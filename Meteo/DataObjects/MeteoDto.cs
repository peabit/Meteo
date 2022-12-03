namespace Meteo.DataObjects;

public sealed record MeteoDto
{
    public double Temperature { get; init; }
    public int Humidity { get; init; }
}