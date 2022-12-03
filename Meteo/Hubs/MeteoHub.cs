using Microsoft.AspNetCore.SignalR;
using Meteo.Services.Interfaces;
using Meteo.Exceptions;

namespace Meteo.Hubs;

public sealed class MeteoHub : Hub
{
    private readonly IMeteoService _meteoService;

    public MeteoHub(IMeteoService meteoService)
        => _meteoService = meteoService;

    public async Task Get()
    {
        try
        {
            var meteoDto = _meteoService.Get();
            await Clients.All.SendAsync("ReceiveMeteo", meteoDto);
        }
        catch (ReadSensorException ex)
        {
            await Clients.All.SendAsync("ReceiveError", ex.Message);
        }
    }
}