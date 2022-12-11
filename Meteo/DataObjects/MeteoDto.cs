namespace Meteo.DataObjects;

public sealed record MeteoDto
{
    public int Temperature { get; init; }
    public int Humidity { get; init; }
}