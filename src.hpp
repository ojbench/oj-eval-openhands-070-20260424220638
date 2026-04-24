

#ifndef SRC_HPP
#define SRC_HPP

#include "cpu.hpp"

namespace sjtu {

    pair<CPUState, uint> CPU_FCFS::run() {
        if (tasks.empty()) {
            state = idle;
            return make_pair(idle, 0);
        }
        
        // FCFS: Execute the first task in the list.
        // Since addTask uses push_back, the first task is at index 0.
        state = busy;
        uint id = tasks[0].task_id;
        tasks[0].time--;
        
        if (tasks[0].time == 0) {
            tasks.erase(tasks.begin());
        }
        
        return make_pair(busy, id);
    }

    pair<CPUState, uint> CPU_SRTF::run() {
        if (tasks.empty()) {
            state = idle;
            return make_pair(idle, 0);
        }

        // SRTF: Execute the task with the shortest remaining time.
        // If multiple tasks have the same shortest time, execute the one that arrived first.
        int best_idx = 0;
        for (int i = 1; i < tasks.size(); ++i) {
            if (tasks[i].time < tasks[best_idx].time) {
                best_idx = i;
            }
            // If times are equal, the one with smaller index arrived first.
        }

        state = busy;
        uint id = tasks[best_idx].task_id;
        tasks[best_idx].time--;

        if (tasks[best_idx].time == 0) {
            tasks.erase(tasks.begin() + best_idx);
        }

        return make_pair(busy, id);
    }

    pair<CPUState, uint> CPU_PRIORITY::run() {
        if (tasks.empty()) {
            state = idle;
            return make_pair(idle, 0);
        }

        // Priority: Execute the task with the highest priority (smallest priority value).
        // If multiple tasks have the same priority, execute the one that arrived first.
        int best_idx = 0;
        for (int i = 1; i < tasks.size(); ++i) {
            if (tasks[i].priority < tasks[best_idx].priority) {
                best_idx = i;
            }
            // If priorities are equal, the one with smaller index arrived first.
        }

        state = busy;
        uint id = tasks[best_idx].task_id;
        tasks[best_idx].time--;

        if (tasks[best_idx].time == 0) {
            tasks.erase(tasks.begin() + best_idx);
        }

        return make_pair(busy, id);
    }

}

#endif

