<?php

namespace Drupal\my_cake\Controller;

class MyCakeController {
  public function cake() {
    return array(
        '#title' =>  'Is there cake?',
        '#markup' => 'I love cake.'
      );
  }
}
