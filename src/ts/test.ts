const test = {
	name: "Hello, World",
	age: 47
};

test.name = "gay"; // Why no error, "strong" typing my ass

console.log(`Hello ${test.name}, hello: ${test.age}`)
