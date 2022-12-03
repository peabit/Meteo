namespace Meteo.Exceptions;

public sealed class ReadSensorException : Exception
{
	public ReadSensorException() : base("Read sensor error") { }
}
