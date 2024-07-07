"""Configures a mitmproxy addon that redirects local requests to the Kalshi demo API.

To use this addon, run mitmproxy with the following command:

$ mitmproxy -s utils/httpser.py

Before running kdeck, override the KALSHI_API_URL cache variable in CMakeUserPresets.json
to the value "http://127.0.0.1:8080/trade-api/v2" and reconfigure/rebuild.
"""

class KProxy:
    def request(self, flow):
        flow.request.scheme = 'https'
        flow.request.host = 'demo-api.kalshi.co'
        flow.request.port = 443


addons = [KProxy()]
