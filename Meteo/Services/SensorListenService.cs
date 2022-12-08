using Meteo.Services.Interfaces;
using Meteo.Exceptions;
using Microsoft.AspNetCore.SignalR;
using Meteo.Hubs;

namespace Meteo.Services
{
    public class SensorListenService : BackgroundService
    {
        private readonly IServiceProvider _serviceProvider;
        private readonly IMeteoService _meteoService;

        public SensorListenService(IServiceProvider serviceProvider, IMeteoService meteoService)
        {
            _serviceProvider = serviceProvider;
            _meteoService = meteoService;
        }

        protected override async Task ExecuteAsync(CancellationToken stoppingToken)
        {
            while (!stoppingToken.IsCancellationRequested)
            {
                await SendMeteoToHub();
                await Task.Delay(1000);
            }
        }

        private async Task SendMeteoToHub()
        {
            using var serviceScope = _serviceProvider.CreateScope();
            var hub = serviceScope.ServiceProvider.GetRequiredService<IHubContext<MeteoHub>>();

            try
            {
                var meteoDto = _meteoService.Get();
                await hub.Clients.All.SendAsync("ReceiveMeteo", meteoDto);
            }
            catch (ReadSensorException ex)
            {
                await hub.Clients.All.SendAsync("ReceiveError", ex.Message);
            }
        }
    }
}