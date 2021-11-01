import collections
import requests
import json

# Setting up session to hold the authenticator
session = requests.Session()
session.headers.update({'Authorization' : 'Bearer {209988cf302a397e0b056c2f9d0e}'})

response = session.get(
    "https://candidate.hubteam.com/candidateTest/v3/problem/dataset?userKey=209988cf302a397e0b056c2f9d0e",
    )
data = response.json()
partners = data['partners']

# Extraction of relevant data, the only data that is relevant to us is the person, the dates they are available and the country they are from
# We save the data in the following format, {'country': {'email': 'available dates'}}
countries = {}
for partner in partners:
    country = partner['country']
    email = partner['email']
    dates = partner['availableDates']

    # As it is a 2 day event, if we remove the last day, then we can see the potential start days
    if len(dates) != 0:
        dates.pop()

    if country in countries:
        countries[country][email] = dates
    else:
        countries[country] = {email: dates}

dataToSendBack = {"countries": []}
for country, data in countries.items():
    # Counts the number of people that attend on a certain date
    dateCounter = {}
    datesIndex = 1
    for partner in data.items():
        for date in partner[datesIndex]:
            if date in dateCounter:
                dateCounter[date] = dateCounter[date] + 1
            else:
                dateCounter[date] = 1
    
    # Ordering the dates, this way if there is a tie in the max function, then the earliest gets chosen
    orderedDates = collections.OrderedDict(sorted(dateCounter.items()))
    startDate = max(orderedDates, key=orderedDates.get)
    if dateCounter.get(startDate) == 0:
        startDate = 'null'

    # Now get the people available on this day
    attendeeCount = 0
    attendees = []
    for partner in data.items():
        if startDate in partner[datesIndex]:
            attendees.append(partner[0])
            attendeeCount = attendeeCount + 1

    dataToSendBack["countries"].append({"attendeeCount": attendeeCount, "attendees": attendees, "name": country, "startDate": startDate})

dataInJSON = json.dumps(dataToSendBack)
response = session.post('https://candidate.hubteam.com/candidateTest/v3/problem/result?userKey=209988cf302a397e0b056c2f9d0e', data = dataInJSON)
print(response.content)