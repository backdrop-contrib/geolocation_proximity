Geolocation Proximity with Smart IP
===================================

Provides Smart IP and Device Geolocation integration for Geolocation Proximity.

Device Geolocation provides visitor's geographical location using client device
location source that implements W3C Geolocation API whereas the coordinates are
geocoded using Google Geocoding service. 

Smart IP is the last fallback if W3C Geolocation API failed. Even if the visitors refuses 
to share their location, the geographical information provided by Smart IP will be used 
to know your visitors' geolocation details.


Installation
------------

- Install this module, Geolocation Proximity and Smart IP (optionally
  with Device Geolocation) using the official Backdrop CMS instructions at
  https://backdropcms.org/guide/modules

- Configure Smart IP and Device Geolocation settings at
  /admin/config/people/smart_ip.

- Create a view with the distance field or filter provided by Geolocation
  Proximity, and leave the latitude and longitude values empty to rely on
  Smart IP and Device Geolocation to set the client geolocation as origin.
