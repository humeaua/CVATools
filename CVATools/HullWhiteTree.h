//
//  HullWhiteTree.h
//  CVATools
//
//  Created by Alexandre HUMEAU on 14/09/14.
//
//

#ifndef CVATools_HullWhiteTree_h
#define CVATools_HullWhiteTree_h

#include <iostream>
#include <math.h>
#include <map>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <string>
#include <algorithm>

namespace numericalmethods
{
    
    struct IsGreaterThan : public std::unary_function<double, bool>
    {
        double val;
        
        IsGreaterThan(double val) : val(val)
        {}
        
        bool operator() (double input)
        {
            return ( input > val);
        }
    };
    
    template<typename KeyType, typename ValueType>
    ValueType interpolate(std::map<KeyType, ValueType>& input, KeyType maturity)
    {
        std::vector<double> keys;
        typedef std::map<KeyType, ValueType> MapType;
        
        for (typename MapType::iterator it = input.begin(); it != input.end(); ++it)
        {
            keys.push_back(it->first);
        }
        
        std::sort(keys.begin(), keys.end());
        IsGreaterThan uf(maturity);
        std::vector<double>::iterator it = std::find_if(keys.begin(), keys.end(), uf);
        if (it == keys.end())
        {
            return input[*(--it)];
        }
        else if (it == keys.begin())
        {
            return input[*keys.begin()];
        }
        else
        {
            it--;
            double prev_x = *it;
            double next_x = *(it + 1);
            double prev_y = input[prev_x];
            double next_y = input[next_x];
            
            return prev_y + (next_y - prev_y) / (next_x - prev_x) * (maturity - prev_x);
        }
    }
    
    template<typename ResultType>
    ResultType newtonRaphsonRootFinder(ResultType(*y)(ResultType), ResultType initialEstimate, double value, double precision, double delta)
    {
        ResultType input = initialEstimate;
        ResultType yorig;
        do
        {
            if (input < 0 || input > 1)
            {
                input = 0;
            }
            yorig = (100 * y(input)) - value;
            ResultType ydelta = 100 * y(input + delta);
            ResultType ydelta1 = 100 * y(input - delta);
            double yder = (ydelta - ydelta1) / (2 * delta);
            if (yder == 0)
            {
                input = input + 0.1;
            }
            else
            {
                input = input - (yorig / yder);
            }
        } while (yorig > precision || yorig < -precision);
        
        return input;
    }
}

class TermStructure {
    typedef std::map<double, double> MapType;
    MapType zeroCoupons;
    
    double B(double t, double T, double a)
    {
        return (1 - exp(-a * (T - t))) / a;
    }
public:
    
    TermStructure(std::map<double, double>& zeroCoupons) : zeroCoupons(zeroCoupons)
    {}
    
    double getRate(double maturity)
    {
        if (zeroCoupons.find(maturity) == zeroCoupons.end())
        {
            return numericalmethods::interpolate(zeroCoupons, maturity);
        }
        return zeroCoupons[maturity];
    }
    
    double getPrice(double maturity)
    {
        if (maturity == 0)
            return 1;
        return exp(-getRate(maturity) * maturity);
    }
    
    double forwardPriceDiscrete(double t, double T, double vol, double dt, double a, double rate)
    {
        // eq in hull book 7th edition 30.25..30.27
        double ln_ahat_t_T = log(getPrice(T) / getPrice(t)) - (B(t, T, a) / B(t, t + dt, a)) * log(getPrice(t + dt) / getPrice(t));
        ln_ahat_t_T -= (pow(vol, 2) / (4 * a)) * B(t, T, a) * (B(t, T, a) - B(t, t + dt, a)) * (1 - exp(-2 * a * t));
        double ahat_t_T = exp(ln_ahat_t_T);
        
        double bhat_t_T = B(t, T, a) / B(t, t + dt, a) * dt;
        return ahat_t_T * exp(-bhat_t_T * rate);
    }
};

enum OptionSide
{
    CALL,
    PUT
};

class IRTrinomialTree {
private:
    double alpha, sigma;
    int N;
    double T;
    double dr, dt;
    double M;
    int jMax;
    TermStructure& term;
    friend class TTNode;
    
    struct TTNode
    {
    private:
        
        double getNextCouponDate(double curr_time, double coupon_freq)
        {
            double temp = coupon_freq;
            while (curr_time >= temp)
            {
                temp += coupon_freq;
            }
            return temp;
        }
    public:
        double r, Q, pu, pm, pd;
        double bondPrice;
        double holdingValue;
        int idx;
        
        TTNode() : r(0), Q(0), pm(0), pu(0), pd(0), bondPrice(0.0), holdingValue(0.0), idx(0)
        {}
        
        void calculateBondPrice(double coupon, double coupon_freq, double maturity, double timestep, double alpha, IRTrinomialTree & tree)
        {
            bondPrice = 0.0;
            
            double curr_time = timestep * tree.dt;
            double nextCoupon = getNextCouponDate(curr_time, coupon_freq);
            while (nextCoupon <= maturity)
            {
                double fp = tree.term.forwardPriceDiscrete(curr_time, nextCoupon, tree.sigma, tree.dt, tree.alpha, r + alpha);
                if (maturity == nextCoupon)
                {
                    bondPrice += (1 + coupon) * fp;
                }
                else
                {
                    bondPrice += coupon * fp;
                }
                nextCoupon += coupon_freq;
            }
        }
        
        double getHoldingValue(int timestep, IRTrinomialTree & tree)
        {
            return holdingValue * exp((-r + tree.layers[timestep].alpha_displ) * tree.dt);
        }
        
        double calculateOptionPrice(double strike, double accrual, int timestep, IRTrinomialTree & tree, OptionSide type)
        {
            double hVal = getHoldingValue(timestep, tree);
            double cash_strike = (strike + accrual);
            double cash_bond = bondPrice;
            double call_payoff = cash_bond - cash_strike;
            double put_payoff = cash_strike - cash_bond;
            if (type == CALL)
            {
                return (call_payoff > hVal) ? call_payoff : hVal;
            }
            else
            {
                return (put_payoff > hVal) ? put_payoff : hVal;
            }
        }
    };
    
    struct TTLayer
    {
        typedef std::map<int, TTNode> NODE_MAP_TYPE;
        typedef NODE_MAP_TYPE::iterator NODE_MAP_ITERATOR_TYPE;
        NODE_MAP_TYPE nodes;
        double alpha_displ;
        double accrual;
        
        struct NodeConnection
        {
            TTNode* node;
            double prob;
            
            NodeConnection(TTNode& node, double prob) : node(&node), prob(prob)
            {}
            
            NodeConnection(const NodeConnection & rhs) : node(rhs.node), prob(rhs.prob)
            {}
        };
        
        void buildLayer(int timestep, IRTrinomialTree & tree)
        {
            timestep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            for (int i = -timestep; i <= timestep; i++)
            {
                nodes[i].idx = i;
                nodes[i].r = i * tree.dr;
                
                if (abs(i) < tree.jMax)
                {
                    nodes[i].pu = 1.0 / 6.0 + (pow((double) i, 2) * pow(tree.M, 2) + i * tree.M) / 2;
                    nodes[i].pm = 2.0 / 3.0 - (pow((double) i, 2) * pow(tree.M, 2));
                    nodes[i].pd = 1 - nodes[i].pu - nodes[i].pm;
                }
                else if (i == tree.jMax)
                {
                    nodes[i].pu = 7.0 / 6.0 + (pow((double) i, 2) * pow(tree.M, 2) + 3 * i * tree.M) / 2;
                    nodes[i].pm = -1.0 / 3.0 - (pow((double) i, 2) * pow(tree.M, 2)) - 2 * i * tree.M;
                    nodes[i].pd = 1 - nodes[i].pu - nodes[i].pm;
                }
                else if (i == -tree.jMax)
                {
                    nodes[i].pd = 7.0 / 6.0 + (pow((double) i, 2) * pow(tree.M, 2) - 3 * i * tree.M) / 2;
                    nodes[i].pm = -1.0 / 3.0 - (pow((double) i, 2) * pow(tree.M, 2) - 2 * i * tree.M);
                    nodes[i].pu = 1 - nodes[i].pd - nodes[i].pm;
                }
            }
        }
        
        std::vector<NodeConnection> getBackConnectedNodes(int nodestep, TTLayer& prevLayer, IRTrinomialTree & tree)
        {
            std::vector<NodeConnection> connectedNodes;
            NODE_MAP_ITERATOR_TYPE it;
            int nodeidx = nodestep;
            int jmax = tree.jMax;
            
            // the edge nodes get special treatment
            if ((prevLayer.nodes.size() == nodes.size()) && (nodeidx == jmax))
            {
                if ((it = prevLayer.nodes.find(nodeidx - 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pu));
                }
                if ((it = prevLayer.nodes.find(nodeidx)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pu));
                }
            }
            else if ((prevLayer.nodes.size() == nodes.size()) && (nodeidx == -jmax))
            {
                if ((it = prevLayer.nodes.find(nodeidx - 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pd));
                }
                if ((it = prevLayer.nodes.find(nodeidx)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pd));
                }
            }
            else if ((prevLayer.nodes.size() == nodes.size()) && (nodeidx == jmax - 1))
            {
                if ((it = prevLayer.nodes.find(nodeidx - 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pu));
                }
                if ((it = prevLayer.nodes.find(nodeidx)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pm));
                }
                if ((it = prevLayer.nodes.find(nodeidx + 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pm));
                }
            }
            else if ((prevLayer.nodes.size() == nodes.size()) && (nodeidx == -(jmax - 1)))
            {
                if ((it = prevLayer.nodes.find(nodeidx - 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pm));
                }
                if ((it = prevLayer.nodes.find(nodeidx)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pm));
                }
                if ((it = prevLayer.nodes.find(nodeidx + 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pd));
                }
            }
            else
            {
                if ((it = prevLayer.nodes.find(nodeidx - 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pu));
                }
                if ((it = prevLayer.nodes.find(nodeidx)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pm));
                }
                if ((it = prevLayer.nodes.find(nodeidx + 1)) != prevLayer.nodes.end())
                {
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pd));
                }
            }
            if (prevLayer.nodes.size() == nodes.size())
            {
                int to_adj_node = static_cast<int> (nodes.size() - 1) / 2 - 2;
                int from_adj_node = static_cast<int> (nodes.size() - 1) / 2;
                
                if (to_adj_node == nodeidx)
                {
                    NODE_MAP_ITERATOR_TYPE it = prevLayer.nodes.find(from_adj_node);
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pd));
                }
                else if (-to_adj_node == nodeidx)
                {
                    NODE_MAP_ITERATOR_TYPE it = prevLayer.nodes.find(-from_adj_node);
                    connectedNodes.push_back(NodeConnection(it->second, it->second.pu));
                }
            }
            
            return connectedNodes;
        }
        
        double getNodeProbability(TTNode& node, int jstep, int timestep, IRTrinomialTree& tree)
        {
            if (timestep == 0)
                return 1;
            TTLayer& prevLayer = tree.layers[timestep - 1];
            TTLayer& thisLayer = tree.layers[timestep];
            
            std::vector<NodeConnection> connectedNodes = thisLayer.getBackConnectedNodes(jstep, prevLayer, tree);
            double probability = 0;
            for (std::vector<NodeConnection>::iterator it = connectedNodes.begin(); it != connectedNodes.end(); it++)
            {
                probability += thisLayer.getNodeProbability(*(*it).node, (*it).node->idx, timestep - 1, tree) * ((*it).prob);
            }
            return probability;
        }
        
        double getNegativeRateProbability(int timestep, IRTrinomialTree& tree)
        {
            int jstep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            for (int i = -jstep; i <= jstep; i++)
            {
                if (nodes[i].r + this->alpha_displ < 0)
                {
                    return getNodeProbability(nodes[i], i, timestep, tree);
                }
            }
            return 0;
        }
        
        
        void forwardInduce(int timestep, IRTrinomialTree & tree)
        {
            int jstep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            TTLayer& prevLayer = tree.layers[timestep - 1];
            double QSumSum = 0;
            // calculate the Q for each node using forward induction on back nodes
            for (int i = -jstep; i <= jstep; i++)
            {
                double QSum = 0;
                std::vector<NodeConnection> connectedNodes = getBackConnectedNodes(i, prevLayer, tree);
                for (std::vector<NodeConnection>::iterator it = connectedNodes.begin(); it != connectedNodes.end(); it++)
                {
                    QSum += (*it).node->Q * (*it).prob * exp(-(prevLayer.alpha_displ + (*it).node->r) * tree.dt);
                }
                nodes[i].Q = QSum;
                QSumSum += (QSum) * exp(-nodes[i].r * tree.dt);
            }
            
            double price_of_bond_at_next_step = exp(-tree.term.getRate((double) (timestep + 1) * tree.dt) * ((timestep + 1) * tree.dt));
            alpha_displ = (log(QSumSum / price_of_bond_at_next_step)) / tree.dt;
        }
        
        void setAccrual(double coupon, double coupon_freq, double timestep, IRTrinomialTree & tree) {
            accrual = 0;
            double nextCoupon = coupon_freq, prevCoupon;
            double curr_time = timestep * tree.dt;
            while (curr_time > nextCoupon)
            {
                nextCoupon += coupon_freq;
            }
            prevCoupon = nextCoupon - coupon_freq;
            if (nextCoupon != curr_time)
            {
                accrual = coupon * (curr_time - prevCoupon);
            }
        }
        
        void calculateBondPrice(double coupon, double coupon_freq, double maturity, int timestep, IRTrinomialTree & tree)
        {
            int jstep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            for (int i = -jstep; i <= jstep; i++)
            {
                setAccrual(coupon, coupon_freq, timestep, tree);
                nodes[i].calculateBondPrice(coupon, coupon_freq, maturity, timestep, alpha_displ, tree);
            }
        }
        
        double calculateEuropeanOptionPrice(int timestep, double strike, IRTrinomialTree & tree, OptionSide type)
        {
            int jstep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            double sum = 0;
            for (int i = -jstep; i <= jstep; i++)
            {
                sum += nodes[i].calculateOptionPrice(strike, accrual, timestep, tree, type) * nodes[i].Q;
            }
            return sum;
        }
        
        double calculateAmericanOptionPrice(int timestep, double strike, IRTrinomialTree & tree, OptionSide type)
        {
            int jstep = (timestep >= tree.jMax) ? tree.jMax : timestep;
            double optionPrice;
            for (int i = -jstep; i <= jstep; i++)
            {
                optionPrice = nodes[i].calculateOptionPrice(strike, accrual, timestep, tree, type);
                if (timestep > 0)
                {
                    TTLayer& prevLayer = tree.layers[timestep - 1];
                    
                    //backward induce the holding value to all connected nodes
                    std::vector<NodeConnection> connectedNodes = getBackConnectedNodes(i, prevLayer, tree);
                    for (std::vector<NodeConnection>::iterator it = connectedNodes.begin(); it != connectedNodes.end(); it++)
                        it->node->holdingValue += optionPrice * it->prob;
                }
            }
            return optionPrice;
        }
    };
    
    
    std::vector<TTLayer> layers;
    
    void buildTreeStep1()
    {
        for (int i = 0; i < N; i++)
        {
            TTLayer layer;
            layer.buildLayer(i, *this);
            layers.insert(layers.end(), layer);
        }
    }
    
    void buildTreeStep2()
    {
        layers[0].nodes[0].Q = 1;
        layers[0].alpha_displ = term.getRate(dt);
        for (int i = 1; i < N; i++)
        {
            layers[i].forwardInduce(i, *this);
        }
    }
    
    void printLayer(int timestep, TTLayer& layerToPrint)
    {
        int jStep = (timestep >= jMax) ? jMax : timestep;
        for (int i = jStep; i >= -jStep; i--) {
            std::stringstream sstream;
            (i >= 0) ? sstream << i : sstream << "M" << -i;
            std::cout << "node" << timestep << sstream.str() << "[ label = \"  timestep = "
            << timestep * dt << "\\n r = "
            << layerToPrint.nodes[i].r << "\\n pu = "
            << layerToPrint.nodes[i].pu << "\\n pm = "
            << layerToPrint.nodes[i].pm << "\\n pd = "
            << layerToPrint.nodes[i].pd
            << "\\n Q = "
            << layerToPrint.nodes[i].Q << "\\n alpha = "
            << layerToPrint.alpha_displ << "\\n rate = "
            << layerToPrint.alpha_displ + layerToPrint.nodes[i].r << "\\n bond price = "
            << layerToPrint.nodes[i].bondPrice
            << "\\n accrual = "
            << layerToPrint.accrual << "\\n holdingValue = "
            << layerToPrint.nodes[i].getHoldingValue(timestep, *this)
            //<< "\\n option price = "
            //<< layerToPrint.nodes[i].calculateOptionPrice(0.6, timestep, *this)
            << "\" ] "
            << std::endl;
        }
    }
    
    void connectLayer(int timestep, TTLayer& layerToPrint)
    {
        int jStep = (timestep >= jMax) ? jMax : timestep;
        for (int i = jStep; i >= -jStep; i--)
        {
            std::stringstream sstream, sstreamm1, sstreamp1, curnode;
            int midNode = i;
            if (i == jMax)
            {
                midNode = i - 1;
            }
            else if (i == -jMax)
            {
                midNode = i + 1;
            }
            (i >= 0) ? curnode << i : curnode << "M" << abs(i);
            (midNode >= 0) ? sstream << midNode : sstream << "M" << abs(midNode);
            (midNode - 1 >= 0) ? sstreamm1 << midNode - 1 : sstreamm1 << "M" << abs(midNode - 1);
            (midNode + 1 >= 0) ? sstreamp1 << midNode + 1 : sstreamp1 << "M" << abs(midNode + 1);
            
            
            std::cout << "node" << timestep << curnode.str() << " -> " << "node" << timestep + 1 << sstreamm1.str() << std::endl;
            std::cout << "node" << timestep << curnode.str() << " -> " << "node" << timestep + 1 << sstream.str() << std::endl;
            std::cout << "node" << timestep << curnode.str() << " -> " << "node" << timestep + 1 << sstreamp1.str() << std::endl;
        }
    }
    
    
    
public:
    
    /**
     * @param alpha
     * @param sigma
     * @param N - number of steps to take
     * @param T - number of years to create the tree for
     * @param term
     */
    IRTrinomialTree(double alpha, double sigma, int N, int T, TermStructure& term, bool debug) : sigma(sigma), alpha(alpha), N(N + 1), T(T),
    dt((double) T / N),
    term(term)
    {
        dr = sigma * sqrt(3 * dt);
        M = -alpha * dt;
        jMax = static_cast<int> (((ceil(-0.184 / M))));
        if (debug)
        {
            std::cout << "Building step 1, jMax set to " << jMax << std::endl;
        }
        buildTreeStep1();
        if (debug)
        {
            std::cout << "Building step 2.." << std::endl;
        }
        buildTreeStep2();
        if (debug)
        {
            std::cout << "Completed.." << std::endl;
        }
    }
    
    double calculateBondPrice(double coupon, double coupon_freq, double maturity)
    {
        coupon = coupon * coupon_freq;
        for (int i = N - 1; i >= 0; i--)
        {
            layers[i].calculateBondPrice(coupon, coupon_freq, maturity, i, *this);
        }
        
        return layers[0].nodes[0].bondPrice;
    }
    
    double calculateEuropeanOptionPrice(double strike, OptionSide type)
    {
        return layers[N - 1].calculateEuropeanOptionPrice(N - 1, strike, *this, type);
    }
    
    double calculateAmericanOptionPrice(double strike, OptionSide type)
    {
        double price = 0;
        for (int i = N - 1; i >= 0; i--)
            price = layers[i].calculateAmericanOptionPrice(i, strike, *this, type);
        return price;
    }
    
    double getNegativeRateProbability()
    {
        double retVal = 0;
        for (int i = 0; i <= N - 1; i++)
        {
            if ((retVal = layers[i].getNegativeRateProbability(i, *this)) != 0.0)
            {
                return retVal;
            }
        }
        
        return 0;
    }
    
    void printTreeStep()
    {
        
        std::cout << "digraph G {" << std::endl;
        std::cout << "rankdir = LR" << std::endl;
        std::cout << "layout=dot;" << std::endl << "rankdir = LR" << std::endl << "node [ fontsize = 8 " << std::endl << "shape = \"record\"]" << std::endl;
        std::cout << "nodedata [" << "label = \"INPUTS\\n dr = " << dr << "\\n M = " << M << "\\n jMax = " << jMax << "\\n dt = " << dt << "\\n alpha " << alpha << "\\n vol = " << sigma << "\"]" << std::endl;
        for (unsigned int i = 0; i < layers.size(); i++)
        {
            printLayer(i, layers[i]);
        }
        for (unsigned int i = 0; i < layers.size() - 1; i++)
        {
            connectLayer(i, layers[i]);
        }
        
        std::cout << "}" << std::endl;
    }
    
    
};

struct HWTreeOutput
{
    double bondPrice, europeanOPrice, americanOPrice;
};

HWTreeOutput HWTreePricer(double a, double sigma, int iterations, int optionMaturity, std::map<double, double>& zeros, double bondCouponRate, double bondCouponLength, double bondMaturity, double strike, OptionSide side, bool debugtree)
{
    HWTreeOutput output;
    TermStructure term(zeros);
    printf("Pricing Option [a - %.5f, sigma - %.5f, iterations - %d, optionMaturity - %d, bondCouponRate - %.2f, bondCouponLength - %.2f, bondMaturity - %.1f, strike - %.2f, side - %s]\n",
           a, sigma, iterations, optionMaturity, bondCouponRate, bondCouponLength, bondMaturity, strike, side == CALL ? "CALL" : "PUT");
    
    // setup the hull-white tree, 0.1 here is the a, 0.02 is sigma,
    // 3 is number of iterations and 1 is T (length of tree in years)
    IRTrinomialTree hwtree(a, sigma, iterations, optionMaturity, term, debugtree);
    
    // now that our tree is setup run the model to get the price of the bond
    //(e.g. 0.1 coupon rate, semi-annual with 5 year maturity)
    std::cout << "Bond Price Today - " << (output.bondPrice = hwtree.calculateBondPrice(bondCouponRate, bondCouponLength, bondMaturity)) << std::endl;
    
    // once the bond prices are calculated at various points in the lattice,
    // we can get the European option prices by taking expectation of bond prices in the last layer of the tree
    std::cout << "European Option Price Today - " << (output.europeanOPrice = hwtree.calculateEuropeanOptionPrice(strike, side)) << std::endl;
    
    // similarly American option prices can be found but it requires a much more time consuming
    // backward induction
    std::cout << "American Option Price Today - " << (output.americanOPrice = hwtree.calculateAmericanOptionPrice(strike, side)) << std::endl;;
    
    // since we have somewhat forced calibrated by setting sigma we need to ensure that the
    // resulting vol gives up very low probability of negative rates.
    // .. this is done by increasing steps in the trinomial tree
    std::cout << "Negative Rate Probability - " << hwtree.getNegativeRateProbability() << std::endl;
    std::cout << "[Pricing End]" << std::endl;
    if (debugtree)
    {
        hwtree.printTreeStep();
    }
    return output;
}

template <class T>
class csv_istream_iterator : public __gnu_cxx::iterator<std::input_iterator_tag, T>
{
    std::istream * _input;
    char _delim;
    std::string _value;
public:
    
    csv_istream_iterator(char delim = ',') : _input(0), _delim(delim)
    {
    }
    
    csv_istream_iterator(std::istream & in, char delim = ',') : _input(&in), _delim(delim)
    {
        ++ * this;
    }
    
    const T operator *() const
    {
        std::istringstream ss(_value);
        T value;
        ss >> value;
        return value;
    }
    
    std::istream & operator ++()
    {
        if (!getline(*_input, _value, _delim))
        {
            _input = 0;
        }
        return *_input;
    }
    
    bool operator !=(const csv_istream_iterator & rhs) const
    {
        return _input != rhs._input;
    }
};
    
    std::map<double, double> getDiff(std::map<double, double>& a, std::map<double, double>& b)
    {
        std::map<double, double> diff;
        for (std::map<double, double>::iterator it = a.begin(); it != a.end(); it++)
        {
            diff[it->first] = b[it->first] - a[it->first];
        }
        return diff;
    }
    
    std::vector<std::map<double, double> > getYieldCurveDiffs(std::vector<std::map<double, double> >& yieldCurves)
    {
        std::vector<std::map<double, double> >::iterator it = yieldCurves.begin();
        std::vector<std::map<double, double> >::iterator it_10 = it + 10;
        std::vector<std::map<double, double> > diffVector;
        while (it != yieldCurves.end() && it_10 != yieldCurves.end())
        {
            diffVector.insert(diffVector.end(), getDiff(*it, *it_10));
            it++;
            it_10++;
        }
        
        return diffVector;
    }
    
    std::map<double, double> applyDiffsToZeros(std::map<double, double>& zeros, std::map<double, double>& diff)
    {
        std::map<double, double> zerosMod;
        TermStructure term(diff); // hack, just to be able to interpolate the values
        for (std::map<double, double>::iterator it = zeros.begin(); it != zeros.end(); it++)
        {
            zerosMod[it->first] = it->second + term.getRate(it->first);
        }
        
        return zerosMod;
    }
    
    std::map<double, double> getInputZeroCoupons()
    {
        std::map<double, double> yield_curve;
        
        yield_curve[1.0 / 12.0] = 0.22994 / 100;
        yield_curve[1.0 / 4.0] = 0.35022 / 100;
        yield_curve[1] = 0.4478 / 100;
        yield_curve[2] = 0.50479 / 100;
        yield_curve[3] = 0.56793 / 100;
        yield_curve[4] = 0.94326 / 100;
        yield_curve[5] = 1.26067 / 100;
        
        return yield_curve;
    }
    
    std::vector<std::map<double, double> > readVarFile()
    {
        std::vector<std::map<double, double> > yieldCurveVector;
        std::ifstream fin("varfile.csv");
        
        if (fin) {
            csv_istream_iterator<double> c(fin);
            int count = 1;
            do {
                std::map<double, double> y;
                double arr[] = {1.0, 3.0, 6.0, 12.0, 24.0, 36.0,60.0};
                for (int i = 0; i <=6; i++) {
                    y[arr[i]/12.0] = (*c)/100;
                    ++c;
                }
                
                yieldCurveVector.insert(yieldCurveVector.end(), y);
                std::cout << "Read line " << count++ << std::endl;
            } while ((c != csv_istream_iterator<double>()));
            fin.close();
        }
        
        std::cout << "First Record... ";
        for (std::map<double, double>::iterator it = yieldCurveVector[0].begin(); it != yieldCurveVector[0].end(); it++)
            std::cout << it->first << "-" << it->second << std::endl;
        
        std::cout << "Last Record... ";
        for (std::map<double, double>::iterator it = yieldCurveVector[yieldCurveVector.size() - 2].begin(); it != yieldCurveVector[yieldCurveVector.size() - 2].end(); it++)
            std::cout << it->first << "-" << it->second << std::endl;
        
        return yieldCurveVector;
    }
    
    void doGreeks(HWTreeOutput hwOrig, double a, double sigma, int iterations, int optionMaturity, std::map<double, double> zeros, double bondCouponRate, double bondCouponLength, double bondMaturity, double strike, OptionSide side, bool debugtree)
    {
        typedef std::map<double, double> MAP_TYPE;
        MAP_TYPE zeros_minus, zeros_plus, zeros_minus_minus, zeros_plus_plus;
        
        double parallel_shift_delta = 0.0001;
        for ( MAP_TYPE::iterator it = zeros.begin(); it != zeros.end(); it++ )  {
            zeros_minus[it->first] = it->second - parallel_shift_delta;
            zeros_plus[it->first] = it->second + parallel_shift_delta;
        }
        
        HWTreeOutput hwmOutput = HWTreePricer(a, sigma, iterations, optionMaturity, zeros_minus, bondCouponRate, bondCouponLength, bondMaturity, strike, side, debugtree);
        HWTreeOutput hwpOutput = HWTreePricer(a, sigma, iterations, optionMaturity, zeros_plus, bondCouponRate, bondCouponLength, bondMaturity, strike, side, debugtree);
        
        HWTreeOutput hwmsigOutput = HWTreePricer(a, sigma - parallel_shift_delta, iterations, optionMaturity, zeros, bondCouponRate, bondCouponLength, bondMaturity, strike, side, debugtree);
        HWTreeOutput hwpsigOutput = HWTreePricer(a, sigma + parallel_shift_delta, iterations, optionMaturity, zeros, bondCouponRate, bondCouponLength, bondMaturity, strike, side, debugtree);
        
        double eODV01, aODV01;
        eODV01 = (hwmOutput.europeanOPrice - hwpOutput.europeanOPrice)/(2 * hwOrig.europeanOPrice * parallel_shift_delta);
        aODV01 = (hwmOutput.americanOPrice - hwpOutput.americanOPrice)/(2 * hwOrig.americanOPrice * parallel_shift_delta);
        
        double eOGamma, aOGamma;
        eOGamma = (hwmOutput.europeanOPrice - 2 * hwOrig.europeanOPrice +  hwpOutput.europeanOPrice)/(100 * hwOrig.europeanOPrice * pow((double)parallel_shift_delta, 2));
        aOGamma = (hwmOutput.americanOPrice - 2 * hwOrig.americanOPrice +  hwpOutput.americanOPrice)/(100 * hwOrig.americanOPrice * pow((double)parallel_shift_delta, 2));
        
        double eOVega, aOVega;
        eOVega = (hwmsigOutput.europeanOPrice - hwpsigOutput.europeanOPrice)/(2 * hwOrig.europeanOPrice * parallel_shift_delta);
        aOVega = (hwmsigOutput.americanOPrice - hwpsigOutput.americanOPrice)/(2 * hwOrig.americanOPrice * parallel_shift_delta);
        
        printf("[Greeks Calculations on Options - European Option Duration: %.5f, American Option Duration: %.5f, European Option Convexity: %.5f, American Option Convexity: %.5f, European Option Vega: %.5f, American Option Vega: %.5f]", eODV01, aODV01, eOGamma, aOGamma, eOVega, aOVega);
        std::cout << std::endl;
        
    }
    
#endif
#ifdef __VAR_CALCULATION__
    int main(int argc, char * args[])
    {
        
        std::vector<std::map<double, double> > yieldCurveVector = readVarFile();
        vector<std::map<double, double> > diffs = getYieldCurveDiffs(yieldCurveVector);
        std::cout << "Diff Completed, size of diff vector is " << diffs.size() << std::endl;
        
        std::map<double, double> zeros = getInputZeroCoupons();
        HWTreeOutput hwPricesOrig = HWTreePricer(0.002, 0.0115, 100, 1, zeros, 0.1, 0.5, 5, 1.42759, PUT, false);
        std::vector<HWTreeOutput> outputVector;
        for (vector<std::map<double, double> >::iterator it = diffs.begin(); it != diffs.end(); it++)
        {
            std::map<double, double> zerosMod = applyDiffsToZeros(zeros, *it);
            HWTreeOutput hwOutput = HWTreePricer(0.002, 0.0115, 100, 1, zerosMod, 0.1, 0.5, 5, hwPricesOrig.bondPrice, PUT, false);
            outputVector.insert(outputVector.end(), hwOutput);
        }
        std::vector<double> lossEuropean, lossAmerican;
        for (std::vector<HWTreeOutput>::iterator it = outputVector.begin(); it != outputVector.end(); it++)
        {
            lossEuropean.insert(lossEuropean.end(),(*it).europeanOPrice - hwPricesOrig.europeanOPrice);
            lossAmerican.insert(lossAmerican.end(),(*it).americanOPrice - hwPricesOrig.americanOPrice);
        }
        
        sort(lossEuropean.begin(), lossEuropean.end());
        
        double pe_99 = *(lossEuropean.begin()+int(lossEuropean.size() * 0.99));
        double pe_95 = *(lossEuropean.begin()+int(lossEuropean.size() * 0.95));
        std::cout << "European Option 1% VAR is " << pe_99 << std::endl;
        std::cout << "European Option 5% VAR is " << pe_95 << std::endl;
        
        double pa_99 = *(lossAmerican.begin()+int(lossAmerican.size() * 0.99));
        double pa_95 = *(lossAmerican.begin()+int(lossAmerican.size() * 0.95));
        std::cout << "American Option 1% VAR is " << pa_99 << std::endl;
        std::cout << "American Option 5% VAR is " << pa_95 << std::endl;
        
        return 0;
    }
    
#endif
