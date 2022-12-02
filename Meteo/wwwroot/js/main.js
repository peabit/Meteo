var rate = 500;
var rateValue = document.querySelector("#rateValue");

document.querySelector("#rate").addEventListener("change", (e) => {
    rate = e.target.value * 500;
    rateValue.textContent = rate + " ms";
});

var temperature = document.querySelector("#temperature");

const hubConnection = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

hubConnection.start().then(() => {
    hubConnection.invoke("Get");
});

hubConnection.on("Receive", function (meteoDto) {
    temperature.value = meteoDto;
    setTimeout(() => hubConnection.invoke("Get"), rate);
});