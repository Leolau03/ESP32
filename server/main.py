from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"   

@app.route("/test-route")
def test_route():
    return "Test route"