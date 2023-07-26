# Server
This is a flask server to allow us to communicate with ESP32.

# Setting up Environment
Create a conda environment from the environment config file using [this](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#creating-an-environment-from-an-environment-yml-file) link.

In root directory, run:
```shell
conda env create -f conda_environment.yml
```

# Running
## Running app locally
From root folder (of github project) run:
```shell
python -m flask --app server/main run -p 8080
```
## Exposing server to a public endpoint
Use a service like [ngrok](https://ngrok.com/) to expose the port you are running the server on publicly. After creating an account on ngrok, downloading thier software, setting up ngrok downloaded locally with your auth token, you can run:
```shell
ngrok http 8080
```

This will expose port 8080 to some endpoint that looks something like "https://f93a-2620-101-f000-700-6ed-3f3f-2b56-fd40.ngrok-free.app". In the ESP32 code, you can replace the base endpoint with this URL