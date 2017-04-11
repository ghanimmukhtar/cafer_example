#include <cafer_core/cafer_core.hpp>
#include "../include/data/chatter_data.hpp"

namespace cc = cafer_core;

int main(int argc, char** argv){
    cc::shared_ptr<cc::DatabaseManager::_Wave> wave_1;
    //cc::shared_ptr<cc::DatabaseManager::_Wave> wave_2;

    std::unique_ptr<cc::ManagerQueue<ChatterData>> chatter_manager{new cc::ManagerQueue<ChatterData>()};


    XmlRpc::XmlRpcValue cafer;

    cc::init(argc, argv, "db_manager_node");
    cc::ros_nh->getParam("cafer",cafer);
    cc::DatabaseManager db_manager(cafer["mgmt"], cafer["type"], cafer["freq"]);

    // Retrieve WATCHDOG messages from the management topic.
    db_manager.wait_for_init();
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    db_manager.spin();

    db_manager.add_wave("/greetings/register_hellos"); //add wave 1
    //db_manager.add_wave("/numbers_addition_example/my_numbers_retrieve"); //add wave 2

    db_manager.find_wave_by_name("/greetings/register_hellos", wave_1);

    if (wave_1 != nullptr) {
        ROS_WARN("found greetings node :)");
        wave_1->add_manager(chatter_manager.release(), wave_1->data_topics["my_greetings"]);
    }

    while (ros::ok() && (!db_manager.get_terminate())) {
        db_manager.spin();
        db_manager.update();
        db_manager.sleep();
    }

    return EXIT_SUCCESS;
}
