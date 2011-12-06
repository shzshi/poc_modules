<?php
/**
 * @file
 * Class definitions for the Message Queue module.
 */

class DrupalMessageQueuePool {
  public $machine_name;
  public $description;
  public $distribution;
  protected $brokers;

  public function __construct() {
    // Initialise defaults.
    $this->description = '';
    $this->distribution = MESSAGEQUEUE_DEFAULT_DISTRIBUTION;
    $this->brokers = array();
  }

  /**
   * Add a broker to the pool.
   */
  public function addBroker(DrupalMessageQueueBroker $broker) {
    $this->brokers[] = $broker;
  }

  /**
   * Get a list of all brokers.
   */
  public function getBrokers() {
    return $this->brokers;
  }

  /**
   * Call the broker method.
   */
  public function __call($method, $arguments) {
    // Implement all stomp methods here?
    $broker = $this->getBroker();
    return call_user_func_array(array($broker, $method), $arguments);
  }

  /**
   * Get a DrupalMessageQueueBroker object, based on the distribution algorithm.
   */
  private function getBroker() {
    // TODO: implement using the dist method specified in $distribution:
    // sharding, etc.
    return $this->brokers[0];
  }

}

/**
 * Each transport mechanism (e.g. STOMP, REST, AMQP, etc) must implement this
 * interface.
 */
interface DrupalMessageQueueBroker {
  // TODO: Define standard abstracted interface.
}
