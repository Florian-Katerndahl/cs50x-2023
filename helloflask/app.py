from flask import Flask, render_template, request

app = Flask(__name__)

COLORS = {
    "Harvard Crimson": "red",
    "Yale Blue": "blue",
}

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "GET":
        return render_template("index.html", colors=COLORS)
    else:
        print("Form submitted")
        color = request.form.get("color")
        print(color, COLORS.values())
        if color in COLORS.values():
            return render_template("color.html", color=color)
        return render_template("error.html", color=color)