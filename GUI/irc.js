const spawn = require('child_process').spawn;
const clientIRC = spawn('./client');

window.onload = function () {
    let logDOM = document.getElementById("log");
    let inputDOM = document.getElementById("bottomBar");
    clientIRC.stdout.on('data', (data) => {
        logDOM.innerHTML = logDOM.innerHTML + data;
        console.log(`stdout: ${data}`);
    });
    inputDOM.addEventListener("keydown", function (event) {
        if (event.keyCode == 13) {
            clientIRC.stdin.write(inputDOM.value);
            console.log(inputDOM.value);
            inputDOM.value = "";
        }
    })
}