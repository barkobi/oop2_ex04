#pragma once
#include "vector"
#include "set"
#include "Consts.h"
#include "Shapes.h"
#include "queue"


template <typename T>
class MosaicNode {
public:
    T data;
    std::vector<MosaicNode<T>*> neighbors;

    MosaicNode(T *data) : data(data) {}
    std::vector<MosaicNode<T>> getNeighbor() { return neighbors; };
    void sumNeighborsColors(int *arr) {
        for (auto pad: neighbors)
            if (pad.data != NULL && pad.data->isFree()) {
                arr[pad.data->getColor()]++;
            }
    }

    std::set<MosaicNode<T>> uniteToGroup(Colors color) const{
        std::set<MosaicNode<T>> united;
        data->setFree(false);
        data->setColor(Colors(color));

        std::queue<MosaicNode<T>> q;

        for (auto &pad: neighbors) {
            if (pad.data != NULL && pad.data->getColor() == data->getColor() && pad.data->isFree()) {
                q.push(pad);
                united.insert(pad);
            }
        }

        while (!q.empty()) {
            auto tmp = q.front();
            if (tmp.data == NULL) {
                q.pop();
                continue;
            }
            std::set<MosaicNode<T>> added = tmp.uniteToGroup(color);
            for (auto tmp: added)
                united.insert(tmp);
            q.pop();
        }
        return united;
    }
    int checkExpansionSize(std::set<int> &checked_id, int &added){
        std::queue<MosaicNode<T>> q;

        for (auto &pad: neighbors) {
            if (pad.data != NULL && pad.data->getColor() == pad.data->getColor() && pad.data->isFree() && !checked_id.contains(pad.data->getId())) {
                q.push(pad);
                checked_id.insert(pad->getId());
                added++;
            }
        }

        while (!q.empty()) {
            auto tmp = q.front();
            if (tmp == NULL) {
                q.pop();
                continue;
            }
            tmp->checkExpansionSize(checked_id, added);
            q.pop();
        }
        return added;
    }

    void addNeighbor(const MosaicNode<T>* node) {
        neighbors.push_back(*node);
    }
    bool operator==(const MosaicNode<T> &other) const { return data->id == other.data->id; }

    bool operator!=(const MosaicNode<T> &other) const { return data->id != other.data->id; }

    bool operator<(const MosaicNode<T>& other) const {
        return data->getId() < other.data->getId();
    }
};