/**
 * @author     : He Xiaowei (Clouddon@sina.com)
 * @date       : 2018-05-04
 * @description: Declaration of Module class, base class of all Module types
 * @version    : 1.0
 *
 * @author     : Zhu Fei (feizhu@pku.edu.cn)
 * @date       : 2021-08-06
 * @description: poslish code
 * @version    : 1.1
 */

#pragma once

#include <memory>
#include <vector>
#include <cassert>
#include <iostream>
#include "Base.h"
#include "Log.h"
#include "Core/Typedef.h"
#include "Core/DataTypes.h"
#include "Core/Platform.h"
#include "Framework/FieldTypes.h"
#include "DeclareModuleField.h"

namespace PhysIKA {
class Node;

/**
 * Module, base class of all Module types.
 * A Module is some computation performed on host Node.
 *
 * Usage:
 * 1. Define a Module instance
 * 2. Attach the Module to some Node via calling Node API
 * 3. The Module's computation will be automatically called in simulation loop
 *    while traversing the SceneGraph
 */
class Module : public Base
{
public:
    Module(std::string name = "default");

    ~Module(void) override;

    bool initialize();

    void update();

    /**
     * @brief Check the completeness of input fields
     *
     * @return true, if all input fields are appropriately set.
     * @return false, if any of the input field is empty.
     */
    bool isInputComplete();

    virtual void begin(){};

    virtual bool execute();

    virtual void end(){};

    void setName(std::string name);
    void setParent(Node* node);

    std::string getName();

    Node* getParent()
    {
        if (m_node == NULL)
        {
            Log::sendMessage(Log::Error, "Parent node is not set!");
        }
        return m_node;
    }

    bool isInitialized();

    virtual std::string getModuleType()
    {
        return "Module";
    }

    bool findInputField(Field* field);
    bool addInputField(Field* field);
    bool removeInputField(Field* field);

    std::vector<Field*>& getInputFields()
    {
        return fields_input;
    }

    bool findOutputField(Field* field);
    bool addOutputField(Field* field);
    bool removeOutputField(Field* field);

    std::vector<Field*>& getOutputFields()
    {
        return fields_output;
    }

    bool findParameter(Field* field);
    bool addParameter(Field* field);
    bool removeParameter(Field* field);

    std::vector<Field*>& getParameters()
    {
        return fields_param;
    }

    virtual std::weak_ptr<Module> next()
    {
        return m_module_next;
    }

    void setNext(std::weak_ptr<Module> next_module)
    {
        m_module_next = next_module;
    }

    bool attachField(Field* field, std::string name, std::string desc, bool autoDestroy = true) override;

protected:
    /// \brief Initialization function for each module
    ///
    /// This function is used to initialize internal variables for each module
    /// , it is called after all fields are set.
    virtual bool initializeImpl();

    std::weak_ptr<Module> m_module_next;

private:
    Node*       m_node;
    std::string m_module_name;
    bool        m_initialized;

    bool m_update_required = true;

    std::vector<Field*> fields_input;
    std::vector<Field*> fields_output;
    std::vector<Field*> fields_param;
};
}  // namespace PhysIKA