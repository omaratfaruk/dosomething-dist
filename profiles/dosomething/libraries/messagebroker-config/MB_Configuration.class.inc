<?php

use DoSomething\MBStatTracker\StatHat;

/**
 * MB_Configuration class - functionality related to the Message Broker
 * configuration.
 */
class MB_Configuration
{
  /**
   * Report consumer activity to StatHat service.
   *
   * @var object
   */
  private $statHat;
  
  /**
   * All Message Broker configuration settings - the source of truth.
   *
   * @var object
   */
  private $configSettings;

  /**
   * Constructor for MessageBroker-Config
   *
   * @param array $source
   *   The source of configuration settings. This can be from a file or an
   *   endpoint.
   * @param array $applicationSettings
   *   General application settings for use by all classes in application.
   */
  public function __construct($source, $applicationSettings) {

    $this->configSettings = $this->_gatherSettings($source);

    $this->statHat = new StatHat($applicationSettings['stathat_ez_key'], 'messagebroker-config:');
    $this->statHat->setIsProduction(FALSE);
  }
  
  /**
   * Gather all setting for a specific exchange
   */
  public function exchangeSettings($targetExchange) {
    
    if (isset($this->configSettings->rabbit->exchanges)) {
      foreach($this->configSettings->rabbit->exchanges as $exchange => $exchangeSettings) {
        if ($exchange == $targetExchange) {
          $settings = $exchangeSettings;
        }
      }
    }
    else {
      echo 'Error - No exchange settings found.', PHP_EOL;
    }

    return $settings;
  }
  
  /**
   * Gather all Message Broker configuration settings from the defined source.
   *
   * @param string $source
   *   Source can be the path to a file or a URL to an endpoint.
   */
  private function _gatherSettings($source) {
    
    if (strpos('http://', $source) !== FALSE) {
      echo 'cURL sources are not currently supported.', PHP_EOL;
    }
    elseif (file_exists($source)) {
        $settings = json_decode(implode(file($source)));
        return $settings;
    }
    else {
      echo 'Source: ' . $source . ' not found.', PHP_EOL;
    }

  }
  
}
