import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

db.execute("CREATE TABLE IF NOT EXISTS history (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, uuid INTEGER NOT NULL, symbol VARCHAR(255) NOT NULL, shares INTEGER NOT NULL, price NUMBERIC NOT NULL, action VARCHAR(5) NOT NULL, FOREIGN KEY (uuid) REFERENCES users(id));")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        try:
            shares = int(shares)
        except ValueError:
            return apology("Not an integer")

        if not symbol or shares <= 0:
            return apology("Not a valid stock or share is not a positive integer")

        market_results = lookup(symbol)
        if not market_results:
            return apology("Not a valid stock")

        money = db.execute("SELECT cash FROM users WHERE id = ?;", session["user_id"])[0]["cash"]
        if money - (shares * market_results["price"]) < 0.0:
            return apology("Not enough money")

        money -= shares * market_results["price"]

        db.execute("INSERT INTO history (uuid, symbol, shares, price, action) VALUES (?, ?, ?, ?, ?);",
                   session["user_id"], symbol, shares, market_results["price"], "buy")

        db.execute("UPDATE users SET cash = ? WHERE id = ?;",
                   money, session["user_id"])

        return redirect("/")

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        name = request.form.get("quote")
        if not name:
            return apology("Stock name required")

        quote = lookup(name)
        if not quote:
            return apology("No data for stock found")

        return render_template("quoted.html", data=quote)
    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        if not username:
            return apology("Username is required")
        if db.execute("SELECT username FROM users WHERE username = ?;", username):
            return apology("User already exists")

        pw = request.form.get("password")
        cf = request.form.get("confirmation")
        if not pw or pw != cf:
            return apology("Password required and needs to be repeated")

        db.execute("INSERT INTO users (username, hash) VALUES (?, ?);", username, generate_password_hash(pw))

        flash("Account successfully created!") # TODO: why not working?
        return redirect("/login")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")
