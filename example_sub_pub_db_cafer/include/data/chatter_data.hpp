//
// Created by phlf on 22/07/16.
//
#include "cafer_core/cafer_core.hpp"
#include <std_msgs/String.h>
#include <yaml-cpp/yaml.h>

class ChatterData : public cafer_core::Data {
public:
    using cafer_core::Data::Data;

    virtual std::map<std::string, std::string> get_serialized_data() const override
    {
        std_msgs::String hello_msgs;

        std::map<std::string, std::string> serialized_data;
        YAML::Emitter greeting_yml;

        cafer_core::shared_ptr<std_msgs::String> msg;
        msg = _stored_msg.instantiate<std_msgs::String>();

        hello_msgs.data = msg->data;
        greeting_yml << hello_msgs.data;
        greeting_yml << YAML::Newline;
        serialized_data["my_greetings"] = greeting_yml.c_str();

        return serialized_data;
     }
};
