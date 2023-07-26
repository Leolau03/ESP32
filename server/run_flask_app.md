# Server
This is a flask server to allow us to communicate with ESP32.

# Setting up Environment
Create a conda environment from the environment config file using [this](https://conda.io/projects/conda/en/latest/user-guide/tasks/manage-environments.html#creating-an-environment-from-an-environment-yml-file) link.

In root directory, run:
```shell
conda env create -f conda_environment.yml
```

# Running
From root folder (of github project) run:
```shell
python -m flask --app server/main run -p 8080
```