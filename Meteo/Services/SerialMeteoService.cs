using System.IO.Ports;
using System.Text.RegularExpressions;
using Meteo.DataObjects;
using Meteo.Services.Interfaces;
using Meteo.Exceptions;
using System.Globalization;

namespace Meteo.Services
{
    public sealed class SerialMeteoService : IMeteoService
    {
        private SerialPort? _port;
        private readonly string _portName;
        private readonly int _portSpeed;
        private static readonly object _lock = new();


        public SerialMeteoService(string portName, int portSpeed)
        {
            _portName = portName;
            _portSpeed = portSpeed;
        }

        public MeteoDto? Get()
        {
            string response = string.Empty;

            lock (_lock)
            {
                try
                {
                    if (_port is null)
                    {
                        _port = new SerialPort(_portName, _portSpeed) { DtrEnable = true };
                        _port.Open();
                    }
                    else if (!_port.IsOpen)
                    {
                        _port.Open();
                    }

                    _port.WriteLine("get");
                    response = _port.ReadLine();
                }
                catch
                {
                    throw new ReadSensorException();
                }

                var meteo = ParseResponse(response);

                if (meteo is null)
                {
                    throw new ReadSensorException();
                }

                return meteo;
            }
        }

        MeteoDto? ParseResponse(string response)
        {
            const string successCode = "0";

            var responseRegex = new Regex(@"(\d{1}),(\d{2}),(\d{1,2})\r");
            var parsedResponse = responseRegex.Match(response);

            if (!parsedResponse.Success || parsedResponse.Groups[1].Value != successCode)
            {
                return null;
            }

            return new MeteoDto
            {
                Temperature = Convert.ToInt32(parsedResponse.Groups[2].Value),
                Humidity = Convert.ToInt32(parsedResponse.Groups[3].Value)
            };
        }
    }
}