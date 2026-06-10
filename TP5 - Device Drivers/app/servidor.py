#!/usr/bin/env python3
"""
Servidor web minimalista.
- Lee /dev/sensor cada 1 segundo
- Guarda los Ãºltimos 60 valores
- Sirve los datos en http://localhost:8080/datos
- Sirve la interfaz web en http://localhost:8080/
"""
import threading
import time
import json
from http.server import HTTPServer, BaseHTTPRequestHandler

# Almacén de datos: lista de {tiempo, sensor, valor, unidad}
datos = []
lock  = threading.Lock()

def leer_sensor():
    """Lee /dev/sensor y devuelve (sensor, valor, unidad)"""
    try:
        with open("/dev/sensor", "r") as f:
            linea = f.read().strip()
        # formato: "sensor:0 valor:27 unidad:C"
        partes = {}
        for token in linea.split():
            k, v = token.split(":")
            partes[k] = v
        return int(partes["sensor"]), int(partes["valor"]), partes["unidad"]
    except Exception as e:
        print(f"Error leyendo sensor: {e}")
        return None, None, None

def loop_lectura():
    """Hilo que lee el sensor cada 1 segundo"""
    inicio = time.time()
    while True:
        sensor, valor, unidad = leer_sensor()
        if valor is not None:
            with lock:
                datos.append({
                    "t":      round(time.time() - inicio, 1),
                    "sensor": sensor,
                    "valor":  valor,
                    "unidad": unidad
                })
                # Guardar solo los Ãºltimos 60 puntos
                if len(datos) > 60:
                    datos.pop(0)
        time.sleep(1)

HTML = """<!DOCTYPE html>
<html>
<head>
  <meta charset="utf-8">
  <title>Sensor Driver TP5</title>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  <style>
    body { font-family: sans-serif; background: #1e1e2e; color: #cdd6f4; margin: 0; padding: 20px; }
    h1   { color: #cba6f7; }
    .controles { margin: 16px 0; }
    button {
      padding: 10px 24px; margin-right: 12px; border: none; border-radius: 8px;
      font-size: 15px; cursor: pointer; background: #45475a; color: #cdd6f4;
    }
    button.activo { background: #cba6f7; color: #1e1e2e; font-weight: bold; }
    #estado { margin: 8px 0 16px; font-size: 13px; color: #a6e3a1; }
    canvas  { background: #313244; border-radius: 12px; padding: 12px; }
  </style>
</head>
<body>
  <h1>ðŸ“¡ Sensor Driver â€” TP5</h1>
  <div class="controles">
    <button id="btn0" class="activo" onclick="cambiarSensor(0)">Sensor 0 â€” Temperatura (Â°C)</button>
    <button id="btn1"               onclick="cambiarSensor(1)">Sensor 1 â€” Humedad (%)</button>
  </div>
  <div id="estado">Conectando...</div>
  <canvas id="grafico" width="800" height="350"></canvas>

<script>
let sensorActivo = 0;
let ultimoSensor = 0;

const ctx = document.getElementById('grafico').getContext('2d');
const grafico = new Chart(ctx, {
  type: 'line',
  data: {
    labels: [],
    datasets: [{
      label: 'Temperatura (Â°C)',
      data: [],
      borderColor: '#cba6f7',
      backgroundColor: 'rgba(203,166,247,0.1)',
      borderWidth: 2,
      pointRadius: 3,
      tension: 0.3
    }]
  },
  options: {
    animation: false,
    scales: {
      x: { title: { display: true, text: 'Tiempo (s)', color: '#cdd6f4' },
           ticks: { color: '#cdd6f4' }, grid: { color: '#45475a' } },
      y: { title: { display: true, text: 'Valor', color: '#cdd6f4' },
           ticks: { color: '#cdd6f4' }, grid: { color: '#45475a' } }
    },
    plugins: { legend: { labels: { color: '#cdd6f4' } } }
  }
});

function cambiarSensor(n) {
  sensorActivo = n;
  fetch('/cambiar?sensor=' + n);
  document.getElementById('btn0').className = n === 0 ? 'activo' : '';
  document.getElementById('btn1').className = n === 1 ? 'activo' : '';
}

function actualizar() {
  fetch('/datos')
    .then(r => r.json())
    .then(d => {
      document.getElementById('estado').textContent =
        d.length ? 'Ãšltimo valor: ' + d[d.length-1].valor + ' ' + d[d.length-1].unidad : 'Sin datos';

      // Si cambiÃ³ el sensor, limpiar el grÃ¡fico
      if (d.length && d[d.length-1].sensor !== ultimoSensor) {
        ultimoSensor = d[d.length-1].sensor;
        grafico.data.labels = [];
        grafico.data.datasets[0].data = [];
      }

      grafico.data.labels = d.map(p => p.t + 's');
      grafico.data.datasets[0].data = d.map(p => p.valor);

      const etiqueta = sensorActivo === 0 ? 'Temperatura (Â°C)' : 'Humedad (%)';
      grafico.data.datasets[0].label = etiqueta;
      grafico.options.scales.y.title.text = etiqueta;
      grafico.update();
    });
}

setInterval(actualizar, 1000);
actualizar();
</script>
</body>
</html>
"""

class Handler(BaseHTTPRequestHandler):
    def log_message(self, *args):
        pass  # silenciar logs HTTP en consola

    def do_GET(self):
        if self.path == "/":
            self.send_response(200)
            self.send_header("Content-Type", "text/html")
            self.end_headers()
            self.wfile.write(HTML.encode())

        elif self.path == "/datos":
            with lock:
                copia = list(datos)
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Access-Control-Allow-Origin", "*")
            self.end_headers()
            self.wfile.write(json.dumps(copia).encode())

        elif self.path.startswith("/cambiar"):
            # /cambiar?sensor=1
            try:
                n = self.path.split("=")[1][0]
                with open("/dev/sensor", "w") as f:
                    f.write(n)
            except Exception as e:
                print(f"Error cambiando sensor: {e}")
            self.send_response(200)
            self.end_headers()

        else:
            self.send_response(404)
            self.end_headers()

if __name__ == "__main__":
    hilo = threading.Thread(target=loop_lectura, daemon=True)
    hilo.start()
    print("Servidor corriendo en http://0.0.0.0:8080")
    print("Abrí­ http://localhost:8080 en tu navegador")
    HTTPServer(("0.0.0.0", 8080), Handler).serve_forever()