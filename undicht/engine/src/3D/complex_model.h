#ifndef COMPLEX_MODEL_H_INCLUDED
#define COMPLEX_MODEL_H_INCLUDED

#include <3D/object.h>
#include <3D/textured_model.h>
#include <core/event_logger.h>

namespace undicht {

    template <class SIMPLE_MODEL, int level>
    class ComplexModel {

        /** a class that combines multiple models
        * they can be moved based on a superordinated orientation
        * @param level: multiple complex models may be "stacked", 0 is the level of the simple model */

        public:

            std::vector<SIMPLE_MODEL> m_sub_models;

            int getLevel() {

                return level;
            }


            int addSubModel(const SIMPLE_MODEL& model) {
                /** @return the id of the model */
                m_sub_models.push_back(model);

                return m_sub_models.size() - 1;
            }

            SIMPLE_MODEL& getSubModel(int id) {

                if(id < m_sub_models.size()) {

                    return m_sub_models.at(id);
                } else {

                    core::EventLogger::storeNote(core::Note(core::UND_ERROR, "ERROR: cant return submodel", UND_CODE_ORIGIN));
                }

            }

            ComplexModel() {

            }

            virtual ~ComplexModel() {

            }

    };

    // some typical uses of the complex model class

    typedef ComplexModel<TexturedModel, 1> ComplexTexturedModel;

} // undicht



#endif // COMPLEX_MODEL_H_INCLUDED
