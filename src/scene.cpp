// COMPOSITE

class Component {

    protected:
        Component *parent_;

    public:
        virtual ~Component() {};
        void SetParent(Component *parent) {
            this->parent_ = parent;
        }

        Component *GetParent() {
            return this->parent_;
        }

};

class Composite {



};