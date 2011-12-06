<?php
/**
 * Message Broker implementation of the STOMP transport protocol.
 * STOMP is a text-based transport (and this implementation relies on the PHP
 * PECL STOMP extension).
 * Being text-based, this is easier to observe and debug, but less performant
 * than binary transport protocols such as AMQP.
 */



class DrupalMessageQueueStompBroker implements DrupalMessageQueueBroker {
  protected $uri;
  protected $username;
  protected $password;

  public function __construct($uri, $username, $password) {
    $this->uri = $uri;
    $this->username = $username;
    $this->password = $password;
  }

  public function __get($property) {
    if (isset($this->$property)) {
      return $this->$property;
    }
  }

  /**
   * Call the stomp method.
   */
  public function __call($method, $arguments) {
    // Implement all stomp methods here?
    $stomp = $this->getStomp();
    drupal_set_message('Calling stomp->' . $method . '(' . implode($arguments, ', ') . ')');
    return call_user_func_array(array($stomp, $method), $arguments);
  }

  /**
   * Get a stomp handler object.
   */
  private function getStomp() {
    static $stomp = null;
    if (is_null($stomp)) {
      drupal_set_message('creating STOMP with: ' . $this->uri);
      include('./sites/all/modules/custom/messagequeue/lib/Stomp.php');
      // $stomp = new Stomp($this->uri, $this->username, $this->password);
      $stomp = new Stomp($this->uri);
      $stomp->connect();
    }
    return $stomp;
  }

  /**
   * Serialization function.
   */
  public function __sleep() {
    return array('uri', 'username', 'password');
  }


}


