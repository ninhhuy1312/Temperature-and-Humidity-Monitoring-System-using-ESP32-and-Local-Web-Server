const express = require('express');
const cors = require('cors');
const app = express();

app.use(cors());
app.use(express.json());

let latestData = { temp: 0, hum: 0 };

// ESP32 POST dữ liệu vào đây
app.post('/', (req, res) => {
  latestData.temp = parseFloat(req.body.temp);
  latestData.hum = parseFloat(req.body.hum);
  console.log('Nhận:', latestData);
  res.send('OK');
});

// Trang web GET dữ liệu mới nhất
app.get('/data', (req, res) => {
  res.json(latestData);
});

app.listen(3000, '0.0.0.0', () => {
  console.log('Server chạy tại port 3000');
});