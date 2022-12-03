var rateControl = document.querySelector("#rate");
var rate = rateControl.value;

document.querySelector("#rate").addEventListener("change", (e) => {
    rate = e.target.value;
});

var temperatureControl = document.querySelector("#temperature");
var humidityControl = document.querySelector("#humidity");

const meteoHub = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

meteoHub.start().then(() => {
    meteoHub.invoke("Get");
});

meteoHub.on("Receive", (meteoDto) => {
    temperatureControl.value = meteoDto;
    humidityControl.value = meteoDto;

    setTimeout(() => meteoHub.invoke("Get"), rate);
});