const hubConnection = new signalR.HubConnectionBuilder()
    .withUrl("/meteo")
    .build();

hubConnection.start().then(() => {
    hubConnection.invoke("Get");
});

hubConnection.on("Receive", function (meteoDto) {
    alert(meteoDto);
});