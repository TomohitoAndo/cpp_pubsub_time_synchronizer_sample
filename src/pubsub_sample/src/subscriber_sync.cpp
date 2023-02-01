#include <functional>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <sample_msgs/msg/int32_stamped.hpp>

// message filter
#include <message_filters/subscriber.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <message_filters/sync_policies/exact_time.h>
#include <message_filters/synchronizer.h>

using sample_msgs::msg::Int32Stamped;
using Int32StampedConstPtr = Int32Stamped::ConstSharedPtr;
using std::placeholders::_1;
namespace sync_policies = message_filters::sync_policies;

class SyncedSubscriber : public rclcpp::Node
{
public:
  using ExactTimeSyncPolicy = sync_policies::ExactTime<Int32Stamped, Int32Stamped>;
  using ExactTimeSynchronizer = message_filters::Synchronizer<ExactTimeSyncPolicy>;

  SyncedSubscriber()
      : Node("minimal_subscriber")
  {
    // Subscribe the input using message filter
    const size_t max_queue_size = 10;
    sub_topic1_.subscribe(
        this, "topic1", rclcpp::SensorDataQoS().keep_last(max_queue_size).get_rmw_qos_profile());
    sub_topic2_.subscribe(
        this, "topic2", rclcpp::SensorDataQoS().keep_last(max_queue_size).get_rmw_qos_profile());

    // sync subscribers with Exact Time Sync Policy
    // sync_inputs_ = std::make_shared<ExactTimeSynchronizer>(ExactTimeSyncPolicy(10), sub_topic1_, sub_topic2_);
    sync_inputs_ = std::make_shared<ExactTimeSynchronizer>(max_queue_size);
    sync_inputs_->connectInput(sub_topic1_, sub_topic2_);
    sync_inputs_->registerCallback(&SyncedSubscriber::synced_topic_callback, this);

    // This is NG in this case
    // sync_inputs_->registerCallback(std::bind(
    //     &SyncedSubscriber::synced_topic_callback, this, std::placeholders::_1, std::placeholders::_2));

    // If arguments for the callback are ConstSharePtr, this is also acceptable
    // sync_inputs_->registerCallback(std::bind(
    //     &SyncedSubscriber::synced_topic_callback_shared_ptr, this, std::placeholders::_1, std::placeholders::_2));

    // this is also OK
    // sync_inputs_->registerCallback(&SyncedSubscriber::synced_topic_callback_shared_ptr, this);
  }

private:
  void synced_topic_callback(const Int32Stamped &msg1, const Int32Stamped &msg2)
  {
    RCLCPP_INFO(this->get_logger(), "topic1: '%d'", msg1.data);
    RCLCPP_INFO(this->get_logger(), "topic2: '%d'", msg2.data);
    RCLCPP_INFO(this->get_logger(), "-----------");
  }

  void synced_topic_callback_shared_ptr(const Int32StampedConstPtr msg1, const Int32StampedConstPtr msg2)
  {
    RCLCPP_INFO(this->get_logger(), "topic1: '%d'", msg1->data);
    RCLCPP_INFO(this->get_logger(), "topic2: '%d'", msg2->data);
    RCLCPP_INFO(this->get_logger(), "-----------");
  }

  message_filters::Subscriber<Int32Stamped> sub_topic1_;
  message_filters::Subscriber<Int32Stamped> sub_topic2_;

  // Synchronized input
  std::shared_ptr<ExactTimeSynchronizer> sync_inputs_;
};

int main(int argc, char *argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<SyncedSubscriber>());
  rclcpp::shutdown();
  return 0;
}
