using Meteo.Hubs;

var builder = WebApplication.CreateBuilder(args);

builder.Services.AddControllersWithViews();
builder.Services.AddSignalR();

var app = builder.Build();
app.UseCors(builder => builder.AllowAnyOrigin());
app.UseDefaultFiles();
app.UseStaticFiles();
app.UseRouting();
app.MapControllers();
app.MapHub<MeteoHub>("/meteo");

app.Run();