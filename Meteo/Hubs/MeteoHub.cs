using Microsoft.AspNetCore.SignalR;

namespace Meteo.Hubs;

public class MeteoHub : Hub
{
    public async Task Get()
    {
        var random = new Random();
        await Clients.All.SendAsync("Receive", random.Next(-30, 30));
    }
}