using Microsoft.AspNetCore.SignalR;

namespace Meteo.Hubs;

public class MeteoHub : Hub
{
    public async Task Get()
    {
        await Clients.All.SendAsync("Receive", "25");
    }
}