<?php

namespace Drupal\exception_handling\Controller;

use Drupal\Core\Controller\ControllerBase;
use Drupal\Core\Database\ExceptionHandler;

class ExceptionHandlingController extends ControllerBase {
   
    var $output;
    
    public function inverse_funct($x) {
        return 1/$x;
    }

    public function except() {
  
        try {
            $this->output .= $this->inverse_funct(1);
            $this->output .= $this->inverse_funct(2);
            $this->output .= $this->inverse_funct(3);
            $this->output .= $this->inverse_funct(5);
            $this->output .= $this->inverse_funct(0);
        }
        catch (\Throwable $e)  {
           \Drupal::logger('widget')->error($e->getMessage());
           $this->output .=  $message = $e->getMessage();
        }
        return [
          '#type' => 'markup',
          '#markup' => $this->t($this->output),
        ];
        
    }
}


