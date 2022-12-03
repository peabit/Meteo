using Meteo.DataObjects;

namespace Meteo.Services.Interfaces;

public interface IMeteoService
{
    MeteoDto Get();
}