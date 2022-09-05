var today = new Date();
var date =
	today.getFullYear() + "-" + (today.getMonth() + 1) + "-" + today.getDate();
var time =
	today.getHours() + ":" + today.getMinutes() + ":" + today.getSeconds();
var dateTime = date + " " + time;

document.getElementById("time").innerHTML = dateTime;

// fetch("https://reqres.in/api/users")
// 	.then((res) => res.json())
// 	.then((data) => console.log(data));

// fetch("https://reqres.in/api/users")
// 	.then((res) => {
// 		if (res.ok) {
// 			console.log(res);
// 		} else {
// 			console.log("failure");
// 		}
// 	})
// 	.then((data) => console.log(data));

// let headers = new Headers();
// headers.append("Content-Type", "application/json");
// headers.append("Accept", "application/json");
// headers.append("origin", "http://192.168.4.1");

// fetch({ method: "POST", headers: headers })
// 	.then((res) => res.json())
// 	.then((data) => console.log(data));

fetchWeights = async () => {
	const response = await fetch("http://192.168.4.1", {
		headers: {
			Accept: "application/json",
			mode: "no-cors",
		},
	});
	const weights = await response.json();

	console.log(weights);
};

fetchWeights();
