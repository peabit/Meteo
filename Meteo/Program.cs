using Meteo.Hubs;
using Meteo.Services.Interfaces;
using Meteo.Services;

var builder = WebApplication.CreateBuilder(args);
builder.Services.AddSignalR();
builder.Services.AddSingleton<IMeteoService>( new SerialMeteoService("COM4", 9600 ));

var app = builder.Build();

app.UseDefaultFiles();
app.UseStaticFiles();

app.MapHub<MeteoHub>("/meteo");

app.Run();