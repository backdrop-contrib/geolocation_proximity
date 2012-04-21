<?php
/**
 * @file
 * Definition of geolocation_proximity_views_handler_filter_distance.
 */

/**
 * General proximity filter for location latitude/longitude.
 */
class geolocation_proximity_views_handler_filter_distance extends views_handler_filter {
  function option_definition() {
    $options = parent::option_definition();
    $options['identifier'] = array('default' => 'dist');
    $options['value'] = array(
      'default' => array(
        'latitude' => '',
        'longitude' => '',
        'search_distance' => 100,
        'search_units' => 'kilometers',
      ),
    );
    return $options;
  }

  function admin_summary() {
    return '';
  }

  function operator_options() {
    return array(
      'dist' => t('Proximity (Circular)'),
    );
  }

  function value_form(&$form, &$form_state) {
    $form['origin'] = array(
      '#type' => 'select',
      '#title' => t('Origin'),
      '#options' => array(
        'static' => t('Static  Latitude / Longitude'),
      ),
      '#description' => t('This will be the way the latitude/longitude of origin is determined.  If this filter is exposed, this will determine the default values. NOTE: The PHP code, nid argument and uid argument options will not be available when the filter is exposed and the use of map is only available when the filter is exposed.'),
      '#default_value' => isset($this->options['origin']) ? $this->options['origin'] : 'static',
    );

    if (!empty($form_state['exposed'])) {
      $identifier = $this->options['expose']['identifier'];
      if (!isset($form_state['input'][$identifier])) {
        // We need to pretend the user already inputted the defaults, because
        // fapi will malfunction otherwise.
        $form_state['input'][$identifier] = $this->value;
      }
    }

    $form['value'] = array(
      '#tree' => TRUE,
    );

    $form['value']['latitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Latitude'),
      '#default_value' => $this->value['latitude'],
      '#weight' => 1,
    );
    $form['value']['longitude'] = array(
      '#type' => 'textfield',
      '#title' => t('Longitude'),
      '#default_value' => $this->value['longitude'],
      '#weight' => 2,
    );
    $form['value']['search_distance'] = array(
      '#type' => 'textfield',
      '#title' => t('Max distance') . ' (km)',
      '#default_value' => $this->value['search_distance'],
      '#weight' => 3,
    );
  }

  function exposed_form(&$form, &$form_state) {
    parent::exposed_form($form, $form_state);
    $key = $this->options['expose']['identifier'];
    $origin = isset($this->options['origin']) ? $this->options['origin'] : 'static';

    unset($form[$key]['php_code']);
    unset($form[$key]['nid_arg']);
    unset($form[$key]['nid_loc_field']);
    unset($form[$key]['uid_arg']);
    unset($form['origin']);
  }

  function query() {
    if (empty($this->value)) {
      return;
    }

    // We need to merge with $this->options['value'] for filter values
    // and $this->value for exposed filter values.
    $options = array_merge($this->options, $this->options['value'], $this->value);

    $filter_lat = $options[0]['latitude'];
    $filter_lng = $options[0]['longitude'];
    $filter_distance = $options[0]['search_distance'];
    if (!(is_numeric($filter_lat) && is_numeric($filter_lng) && is_numeric($filter_distance))) {
      return;
    }

    $this->ensure_my_table();

     // Precalulate some values to speed up the query.
     //
     // http://www.codecodex.com/wiki/Calculate_Distance_Between_Two_Points_on_a_Globe#MySQL
     //
     // acos(
     //   cos( radians(45.20327) ) 
     //   * cos( radians( coord_lat ) ) 
     //   * cos( radians( 23.7806 ) - radians(coord_long) ) 
     //   + 
     //   sin( radians(45.20327) ) 
     //   * sin( radians(coord_lat) ) 
     // ) * 6371
    $filter_lat_cos_rad = cos(deg2rad($filter_lat));
    $filter_lat_sin_rad = sin(deg2rad($filter_lat));
    $filter_lng_rad = deg2rad($filter_lng);

    // Use precalculated values from Geolocation Field.
    $field_id = $options['field'];
    $field_id = str_replace('_distance', '', $field_id);
    // SIN( radians(lat) )
    $field_lat_sin_rad = "$this->table_alias.$field_id" . '_lat_sin';
    // COS( radians(lat) )
    $field_lat_cos_rad = "$this->table_alias.$field_id" . '_lat_cos';
    // radians(lng)
    $field_lng_rad = "$this->table_alias.$field_id" . '_lng_rad';

    // Begin proximity query.
    $this->query->add_where_expression($this->options['group'], " 
      (
        6371 
        * ACOS( 
          $filter_lat_cos_rad 
          * $field_lat_cos_rad 
          * COS( $filter_lng_rad - $field_lng_rad ) 
          + 
          $filter_lat_sin_rad 
          * $field_lat_sin_rad 
        )
      ) < " . $filter_distance);
    // End proximity query.
  }
}
