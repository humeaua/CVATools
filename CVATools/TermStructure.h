//
//  TermStructure.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 19/12/13.
//
//

#ifndef CVATools_TermStructure_h
#define CVATools_TermStructure_h

#include <vector>
#include "Require.h"
#include "Exception.h"
#include "VectorUtilities.h"

//  This file creates a termstructure template

namespace Finance
{
    namespace Base
    {
        template<class T, class U>
        class TermStructure
        {
        public:
            TermStructure()
            {
                TVariables_.resize(1);
                TVariables_[0] = 0;
                
                UValues_.resize(1);
                UValues_[0] = 0;
            }
            
            TermStructure(const std::vector<T> & TVariables, const std::vector<U> & UValues)
            {
                REQUIREEXCEPTION(TVariables.size() == UValues.size(), "Size of variables and values are not the same");
                SetTermStructure(TVariables, UValues);
            }
            
            virtual const std::vector<T> & GetVariables() const
            {
                return TVariables_;
            }
            
            virtual const std::vector<U> & GetValues() const
            {
                return UValues_;
            }
            
            virtual void SetVariables(const std::vector<T> & TVariables)
            {
                TVariables_ = TVariables;
            }
            
            virtual void SetValues(const std::vector<U> & UValues)
            {
                UValues_ = UValues;
            }
            
            virtual void SetTermStructure(const std::vector<T> & TVariables, const std::vector<U> & UValues)
            {
                UValues_ = UValues;
                TVariables_ = TVariables;
            }
            
            virtual bool IsTermStructure() const
            {
                return Size() > 1;
            }
            
            virtual const U & operator ()(const T& variable) const
            {
                //  Flat extrapolation on the left
                if (variable < TVariables_.front())
                {
                    return UValues_.front();
                }
                for (std::size_t i = 0 ; i < TVariables_.size() - 1 ; ++i)
                {
                    //  Right-continuous piecewise constant function
                    if (TVariables_[i] <= variable < TVariables_[i + 1] )
                    {
                        return UValues_[i];
                    }
                }
                
                //  Flat extrapolation on the right
                if (variable >= TVariables_.back())
                {
                    return UValues_.back();
                }
                throw EXCEPTION("error getting term-structure");
            }
            
            virtual void MergeTermStructure(TermStructure<T,U> & sTermStructure)
            {
                if (!IsSameTermStructure(sTermStructure))
                {
                    const size_t iSizeA = Size(), iSizeB = sTermStructure.Size();
                    
                    const std::vector<T> TVariablesA = TVariables_;
                    const std::vector<U> TVariablesB = sTermStructure.GetVariables();
                    
                    const std::vector<T> UValuesA = UValues_;
                    const std::vector<U> UValuesB = sTermStructure.GetValues();
                    
                    std::vector<T> TVariablesMerged;
                    std::vector<U> UValuesAMerged;
                    std::vector<U> UValuesBMerged;
                    
                    int iIndexA = 0, iIndexB = 0;
                    
                    while (iIndexA <= (long)iSizeA && iIndexB <= (long)iSizeB && iIndexA + iIndexB < (long)(iSizeA + iSizeB))
                    {
                        if (iIndexA == (long)iSizeA)
                        {
                            TVariablesMerged.push_back(TVariablesB[iIndexB]);
                            UValuesAMerged.push_back(UValuesA[std::max(0,iIndexA-1)]);
                            UValuesBMerged.push_back(UValuesB[iIndexB]);
                            ++iIndexB;
                        }
                        else if (iIndexB == (long)iSizeB)
                        {
                            TVariablesMerged.push_back(TVariablesA[iIndexA]);
                            UValuesAMerged.push_back(UValuesA[iIndexA]);
                            UValuesBMerged.push_back(UValuesB[std::max(0,iIndexB-1)]);
                            ++iIndexA;
                        }
                        else if (TVariablesA[iIndexA] < TVariablesB[iIndexB])
                        {
                            TVariablesMerged.push_back(TVariablesA[iIndexA]);
                            UValuesAMerged.push_back(UValuesA[iIndexA]);
                            UValuesBMerged.push_back(UValuesB[std::max(0,iIndexB-1)]);
                            ++iIndexA;
                        }
                        else if (TVariablesA[iIndexA] == TVariablesB[iIndexB])
                        {
                            TVariablesMerged.push_back(TVariablesA[iIndexA]);
                            UValuesAMerged.push_back(UValuesA[iIndexA]);
                            UValuesBMerged.push_back(UValuesB[std::max(0,iIndexB-1)]);
                            ++iIndexA;
                            ++iIndexB;
                        }
                        else if (TVariablesA[iIndexA] > TVariablesB[iIndexB])
                        {
                            TVariablesMerged.push_back(TVariablesB[iIndexB]);
                            UValuesAMerged.push_back(UValuesA[std::max(0,iIndexA-1)]);
                            UValuesBMerged.push_back(UValuesB[iIndexB]);
                            ++iIndexB;
                        }
                    }
                    
                    
                    TVariables_ = TVariablesMerged;
                    UValues_ = UValuesAMerged;
                    
                    sTermStructure.SetVariables(TVariablesMerged);
                    sTermStructure.SetValues(UValuesBMerged);
                }
            }
            
            TermStructure<double, U> operator = (const U& value)
            {
                TVariables_.clear();
                UValues_.clear();
                TVariables_.push_back(0.0);
                UValues_.push_back(value);
                return *this;
            }
            
            TermStructure<T,U> operator *= (const TermStructure<T,U> & sTermstructure)
            {
                MergeTermStructure(sTermstructure);
                
                std::vector<U> & UValuesTS = sTermstructure.GetValues();
                
                for (std::size_t i = 0 ; i < TVariables_.size() ; ++i)
                {
                    UValues_[i] *= UValuesTS[i];
                }
                return *this;
            }
            
            template<typename V>
            bool IsSameTermStructure(const TermStructure<T, V> & sTermStructure) const
            {
                return Utilities::AreEqual(TVariables_, sTermStructure.GetVariables());
            }
            
            std::size_t Size() const
            {
                REQUIREEXCEPTION(TVariables_.size() == UValues_.size(), "Size of variables and values are not the same");
                return TVariables_.size();
            }
            
        protected:
            std::vector<T> TVariables_;
            std::vector<U> UValues_;
        };
        
    }
}

#endif
