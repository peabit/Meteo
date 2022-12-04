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

        public SerialMeteoService(string portName, int portSpeed)
        {
            _portName = portName;
            _portSpeed = portSpeed;
        }

        public MeteoDto? Get()
        {
            string response = string.Empty;

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

        MeteoDto? ParseResponse(string response)
        {
            var responseRegex = new Regex(@"(success|error),(-?\d+\.\d+),(\d+)\r");
            var parsedResponse = responseRegex.Match(response);

            if (!parsedResponse.Success || parsedResponse.Groups[1].Value == "error")
            {
                return null;
            }

            var pointDoubleFormtInfo = new NumberFormatInfo { NumberDecimalSeparator = "." };

            return new MeteoDto
            {
                Temperature = Convert.ToDouble(parsedResponse.Groups[2].Value, pointDoubleFormtInfo),
                Humidity = Convert.ToInt32(parsedResponse.Groups[3].Value)
            };
        }
    }
}