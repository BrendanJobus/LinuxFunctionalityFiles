import requests, json

response = requests.get("https://cdn.jsdelivr.net/gh/fawazahmed0/currency-api@1/latest/currencies/eur.json")
print(response.status_code)

data = response.json()
euroToDollar = data["eur"]['usd']
print(euroToDollar)

response = requests.get("http://api.open-notify.org/iss-now.json")

res = response.json()
print(res)
print(res['timestamp'])
print(res['iss_position']['latitude'], res['iss_position']['longitude'])