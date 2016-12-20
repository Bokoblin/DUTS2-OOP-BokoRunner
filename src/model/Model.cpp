#include "Model.h"

using namespace std;

/**
 * Parameterized Constructor
 * @author Arthur, Florian
 * @date 21/02 - 20/12
 */
Model::Model(int w, int h)  :
    m_width(w), m_height(h),
    m_dataBase{nullptr},
    m_appState{INTRO}
{}

/**
 * Copy Constructor
 * @author Arthur
 * @date 14/04 - 20/12
 */
Model::Model(const Model& model) :
    m_width(model.m_width), m_height(model.m_height),
    m_dataBase{model.m_dataBase}, m_appState{model.m_appState}
{}

/**
 * Destructor
 * @author Arthur, Florian
 * @date 21/02 - 26/03
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
 * @date 21/02 - 27/03
 */
void Model::nextStep() {}
