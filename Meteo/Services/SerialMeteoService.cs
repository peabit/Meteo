using System.IO.Ports;
using Meteo.DataObjects;
using Meteo.Services.Interfaces;

namespace Meteo.Services
{
    public class SerialMeteoService : IMeteoService
    {
        private readonly SerialPort _port;

        public SerialMeteoService(string portName, int speed)
            => _port = new SerialPort(portName, speed) { DtrEnable = true };

        public MeteoDto Get()
        {
            if (!_port.IsOpen)
            {
                _port.Open();
            }

            _port.WriteLine("GET");

            var meteoString = _port.ReadLine();
            var meteoRaw = meteoString.Split(';');

            return null;
        }
    }
}