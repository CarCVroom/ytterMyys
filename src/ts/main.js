import * as THREE from 'three';
import create_orbit from './orbit.js'

document.getElementById("start").addEventListener("click", () => {
	start_orbit(400000);
})
const altitude_gauge = document.getElementById("altitude_gauge");
const time_gauge = document.getElementById("time_gauge");

const container = document.getElementById("orbit_area");

const scene = new THREE.Scene();

const camera = new THREE.PerspectiveCamera(
	75,
	container.clientWidth / container.clientHeight,
	1,
	1000000
);

const renderer = new THREE.WebGLRenderer({antialias: true});

renderer.setSize(container.clientWidth, container.clientHeight);
container.appendChild(renderer.domElement);
scene.background = new THREE.Color(0x000000);

camera.position.z = 15000;

// Earth
const geo_earth = new THREE.CircleGeometry( 6371, 64);
const mat_earth = new THREE.MeshBasicMaterial({ color: 0x0000ff});
const earth = new THREE.Mesh(geo_earth, mat_earth);
scene.add(earth);

// Satelite
const geo_satelite = new THREE.CircleGeometry( 50, 64);
const mat_satelite = new THREE.MeshBasicMaterial({ color: 0xff0000});
const satelite = new THREE.Mesh(geo_satelite, mat_satelite);

renderer.render(scene, camera);

const orbit = await create_orbit();

function sleep(ms) {
    	return new Promise(resolve => setTimeout(resolve, ms));
}

async function start_orbit(altitude) {
	// Calls WASM and adds satelite
	
	orbit._orbit_start(altitude);
	let x = orbit._get_x() / 1000;
	let y = orbit._get_y() / 1000;
	let alt = orbit._get_altitude();
	let time_elapsed = orbit._get_time_elapsed();
	altitude_gauge.innerHTML = ` Altitude: ${alt} (m)`;
	time_gauge.innerHTML = ` Time elapsed: ${time_elapsed} (seconds)`;

	satelite.position.set(x, y, 0);
	scene.add(satelite)

	let in_orbit = true;
	while(in_orbit) {
		orbit._orbit_update(alt);
		x = orbit._get_x() / 1000; // m to km
		y = orbit._get_y() / 1000;
		alt = orbit._get_altitude();
		time_elapsed = orbit._get_time_elapsed();
		altitude_gauge.innerHTML = ` Altitude: ${alt} (m)`;
		time_gauge.innerHTML = ` Time elapsed: ${time_elapsed} (seconds)`;

		if (alt < 0) {
			alert("Altitude is less then 1");
			return;
		}

		satelite.position.set(x, y, 0);
		scene.add(satelite)

		renderer.render(scene, camera);

		await sleep(10);
	}
}
