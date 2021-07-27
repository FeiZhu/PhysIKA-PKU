/**
 * @author     : He Xiaowei (Clouddon@sina.com)
 * @date       : 2019-05-14
 * @description: Declaration of PositionBasedFluidModel class, which implements Position-based fluid model
 * @version    : 1.0
 *
 * @author     : Zhu Fei (feizhu@pku.edu.cn)
 * @date       : 2021-07-27
 * @description: poslish code
 * @version    : 1.1
 */

#pragma once

#include "Framework/Framework/NumericalModel.h"
#include "Framework/Framework/FieldVar.h"
#include "Framework/Framework/FieldArray.h"
#include "DensityPBD.h"

namespace PhysIKA {
template <typename TDataType>
class ParticleIntegrator;
template <typename TDataType>
class NeighborQuery;
template <typename TDataType>
class ImplicitViscosity;
class ForceModule;
class ConstraintModule;

/**
 * PositionBasedFluidModel, implementation of the paper <Position Based Fluids>
 * Usage:
 * 1. Define a PositionBasedFluidModel instance
 * 2. Bind the instance with a ParticleFluid node by calling Node::setNumericalModel()
 * 3. Connect fields of ParticleFluid with PositionBasedFluidModel by calling Field::connect()
 * We're done. PositionBasedFluidModel will be employed in advance() of the ParticleFluid.
 *
 * TODO(Zhu Fei): complete the code comments.
 */
template <typename TDataType>
class PositionBasedFluidModel : public NumericalModel
{
    DECLARE_CLASS_1(PositionBasedFluidModel, TDataType)
public:
    typedef typename TDataType::Real  Real;
    typedef typename TDataType::Coord Coord;

    PositionBasedFluidModel();
    virtual ~PositionBasedFluidModel();

    void step(Real dt) override;

    void setSmoothingLength(Real len)
    {
        m_smoothingLength.setValue(len);
    }
    void setRestDensity(Real rho)
    {
        m_restRho = rho;
    }

    void setIncompressibilitySolver(std::shared_ptr<ConstraintModule> solver);
    void setViscositySolver(std::shared_ptr<ConstraintModule> solver);
    void setSurfaceTensionSolver(std::shared_ptr<ForceModule> solver);

    DeviceArrayField<Real>* getDensityField()
    {
        return m_pbdModule->outDensity();
    }

public:
    VarField<Real> m_smoothingLength;

    DeviceArrayField<Coord> m_position;
    DeviceArrayField<Coord> m_velocity;
    DeviceArrayField<Coord> m_forceDensity;

protected:
    bool initializeImpl() override;

private:
    int  m_pNum;
    Real m_restRho;

    std::shared_ptr<ForceModule>      m_surfaceTensionSolver;
    std::shared_ptr<ConstraintModule> m_viscositySolver;
    std::shared_ptr<ConstraintModule> m_incompressibilitySolver;

    std::shared_ptr<DensityPBD<TDataType>>        m_pbdModule;
    std::shared_ptr<ImplicitViscosity<TDataType>> m_visModule;

    std::shared_ptr<ParticleIntegrator<TDataType>> m_integrator;
    std::shared_ptr<NeighborQuery<TDataType>>      m_nbrQuery;
};

#ifdef PRECISION_FLOAT
template class PositionBasedFluidModel<DataType3f>;
#else
template class PositionBasedFluidModel<DataType3d>;
#endif
}  // namespace PhysIKA