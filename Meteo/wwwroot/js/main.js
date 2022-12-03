var rateControl = document.querySelector("#rate");
var rate = rateControl.value;

document.querySelector("#rate").addEventListener("change", (e) => {
    rate = e.target.value;
});

var messageControl = document.querySelector("#message");

const meteoHub = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

meteoHub.start().then(() => {
    meteoHub.invoke("Get");

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
    
    setTimeout(() => meteoHub.invoke("Get"), rate);
});

meteoHub.on("ReceiveError", (error) => {
    messageControl.textContent = "Receive error";
    messageControl.classList.replace("alert-success", "alert-danger");

    temperatureControl.value = null;
    humidityControl.value = null;

    setTimeout(() => meteoHub.invoke("Get"), rate);
});