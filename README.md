Geolocation Proximity
=====================

Backdrop CMS port of the Drupal 7 module
[Geolocation Proximity](https://www.drupal.org/project/geolocation_proximity)

This is a Views distance/proximity filter and field for Geolocation module.


Features
--------

- Views filter that can be used to filter entities (nodes, users, etc.) based
  on distance from a certain point (defined as lat/lng point).

- Use visitor's current location by default (if latitude and longitude are left
  empty), provided by another module implementing
  hook_geolocation_proximity_client_location_alter(). The submodule Geolocation
  Proximity with Smart IP provides integration with
  [Smart IP](https://github.com/backdrop-contrib/smart_ip) to set the visitor's
  geolocation.

- Views field to display the calculated distance between the entity and a
  reference point (can be synced with filters lat/lng values).

- User-friendly input widget for exposed filters using Google's reverse
  geocoder


Installation
------------

- Install this module and Geolocation using the official Backdrop CMS
  instructions at https://backdropcms.org/guide/modules

- Create a view with the distance field or filter provided by Geolocation
  Proximity.
  
- Optionally install the submodule Geolocation Proximity with Smart IP and
  leave the filter's latitude and longitude values empty to rely on Smart IP
  and Device Geolocation to set the client geolocation as origin.


License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.


Current Maintainers
-------------------

- Juan Olalla (https://github.com/juanolalla)
- Seeking additional maintainers.


Credits
-------
- Originally written for Drupal by [Maurizio Pinotti](https://www.drupal.org/u/mauriziopinotti).
- Drupal project maintained by [Jochen Meyer](https://www.drupal.org/u/derjochenmeyer).
- Drupal project also maintained by [Federico Jaramillo](https://www.drupal.org/u/jmfederico).
- Ported to Backdrop CMS by [Juan Olalla](https://github.com/juanolalla).
