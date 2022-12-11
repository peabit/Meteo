var messageControl = document.querySelector("#message");

const meteoHub = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

meteoHub.start().then(() => {
    messageControl.textContent = "Connected";
    messageControl.classList.add("alert-success");
});

var temperatureControl = document.querySelector("#temperature");
var humidityControl = document.querySelector("#humidity");

meteoHub.on("ReceiveMeteo", (meteoDto) => {
    temperatureControl.value = meteoDto.temperature;
    humidityControl.value = meteoDto.humidity;

    messageControl.textContent = "Connected";
    messageControl.classList.replace("alert-danger", "alert-success");
});

meteoHub.on("ReceiveError", ( ) => {
    messageControl.textContent = "Connection error";
    messageControl.classList.replace("alert-success", "alert-danger");

    temperatureControl.value = null;
    humidityControl.value = null;
});