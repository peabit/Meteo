var rateControl = document.querySelector("#rate");
var rate = rateControl.value;

document.querySelector("#rate").addEventListener("change", (e) => {
    rate = e.target.value;
});

var temperatureControl = document.querySelector("#temperature");

const meteoHubConnection = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

meteoHubConnection.start().then(() => {
    meteoHubConnection.invoke("Get");
});

meteoHubConnection.on("Receive", (meteoDto) => {
    temperatureControl.value = meteoDto;
    setTimeout(() => meteoHubConnection.invoke("Get"), rate);
});