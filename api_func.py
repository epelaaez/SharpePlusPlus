import requests
import json

def load_api_key(filepath):
    with open(filepath, "r") as file:
        return file.read().strip()

API_KEY = load_api_key("api.txt")
BASE_URL = "https://www.alphavantage.co/query"

def get_stock_data(
        symbol, 
        function="TIME_SERIES_INTRADAY", 
        outputsize="full",
        adjusted="true",
        interval="60min"
    ):
    """
    Fetch stock data from Alpha Vantage API.
    
    Parameters:
        symbol (str): Stock symbol.
        function (str): The function of the time series (e.g., "TIME_SERIES_INTRADAY").
        outputsize (str): The size of the output. "compact" returns the last 100 data points,
                        "full" returns the full-length time series of up to 20 years of historical data,
                        and a full month for intraday data.
                          
    Returns:
        dict: JSON object containing stock information.
    """
    params = {
        "function": function,
        "symbol": symbol,
        "apikey": API_KEY,
        "adjusted": adjusted,
        "interval": interval,
        "outputsize": outputsize
    }
    
    response = requests.get(BASE_URL, params=params)
    data = response.json()
    
    if "Error Message" in data:
        print(f"Error: {data['Error Message']}")
        return None
    
    return data
