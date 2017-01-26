#include "Model.h"

using namespace std;

/**
 * Constructs a model with app's size
 * @author Arthur, Florian
 * @date 21/02/16 - 20/12/16
 *
 * @param w the app width
 * @param h the app height
 */
Model::Model(int w, int h)  :
    m_width(w), m_height(h),
    m_dataBase{nullptr},
    m_appState{INTRO}
{}

/**
 * Copy Constructor
 * @author Arthur
 * @date 14/04/16 - 20/12/16
 */
Model::Model(const Model& model) :
    m_width(model.m_width), m_height(model.m_height),
    m_dataBase{model.m_dataBase}, m_appState{model.m_appState}
{}

/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02/16 - 26/03/16
 */
Model::~Model() {}


//=== Getters

DataBase *Model::getDataBase() const {return m_dataBase;}
AppState Model::getAppState() const {return m_appState;}


//=== Setters
void Model::setDataBase(DataBase *data) {m_dataBase = data;}
void Model::setAppState(AppState state) { m_appState = state;}


/**
 * Next Step
 * @author Arthur
 * @date 21/02/16 - 27/03/16
 */
void Model::nextStep() {}
