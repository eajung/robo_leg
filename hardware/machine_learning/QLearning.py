#QLearning agent
#Tensegrity arm
#Ash Robbins

import util, random, time
import math


class armAgent:
  #An arm agent to take in the current state and choose the state to go to in order to increase the reward
  #Predicts next state, calculates values and qvalues of states.
  
  #******************************************************************************************
  #init
  #******************************************************************************************
  def __init__(self, goal):
    #Learning data
    self.alpha = .3 #Learning rate
    self.epsilon = .2 #Rate of random action
    self.discount = .73 #Rate next state gets
    self.learning = False #If learning
    
    
    
    #Initialize 
    self.qvals = util.Counter()
    self.weights = util.Counter()
    self.legalActions = [AllActions.UP, AllActions.DOWN, AllActions.FUP, AllActions.FDOWN, AllActions.SUP, AllActions.SDOWN, AllActions.STOP] #TODO: SHOULD DEFINE THESE ASAP
    self.actions = []
    self.states = [] #Should possibly not initialize this here
    self.goal = goal
    
    #Imports weights from file 
    #if self.learning:
    weightFile = open("weights.txt", "r")  
      
    for line in weightFile:
      name, val = str.split(line)
      self.weights[name] = float(val)
      
    weightFile.close()
      
      
    print 'Start'
    
  #******************************************************************************************
  #chooseAction
  #Picks among the possible actions the agent may take
  #******************************************************************************************  
  def chooseAction(self, state, reward):
  
    #TODO: PUT CONSTRAINTS HERE
    x,y,z = state
    print 'Current IMU:', state
    print 'Current Goal:', self.goal
    
    
    if z >= 60 or z<=-60:
      return AllActions.STOP
    #Update if learning
    if self.learning:
      self.update(state, reward)
      
    #Update weight file
    if self.learning:
      weightFile = open("weights.txt", 'w')
      for k in self.weights.sortedKeys():
        weightFile.write( k + " " + str(self.weights[k]) + "\n")
      weightFile.close()
      
      
      
      
    #Possible random choice if learning
    if self.learning and util.flipCoin(self.epsilon):
      #print 'Random action chosen'
      return random.choice(self.legalActions)
      
      
    action = self.getPolicy(state)
    
    #Store previous state and action
    self.actions.append(action)
    self.states.append(state)
    
    print 'Action is ', action
    return action
    
  #******************************************************************************************
  #getQvalue
  #Returns Qvalue of the state, which should be weights multiplied by corresponding features
  #******************************************************************************************
  def getQValue(self, state, action):
  
  
    features = self.getFeatures(state, action)
    
    print 'Action, features:', action, features
    return self.weights*features
    
    
    
  
  #******************************************************************************************
  #getValue
  #Returns max action of the possible Q values at the state given any action
  #******************************************************************************************
  def getValue(self, state):
    
    vals = []
    
    
    for action in self.legalActions:
      vals.append(self.getQValue(state, action))
    
    
    #In case no possible actions? Shouldn't happen but safety is key
    if vals == []:
      return 0
    
    
    return max(vals)
    
    
    
  #*****************************************************************************************
  #getPolicy
  #Gets best action from the given state based on the Q values calculated. If mulitple best
  #Q values, then return a random choice of the best actions
  #******************************************************************************************    
  def getPolicy(self, state):
    
    #Best value of current state
    bestVal = self.getValue(state)
    
    
    bestAction = [AllActions.STOP] #TODO: Make this motor.stop?
    
    
    #Go through actions, append any values resulting in the best value to the best actions
    for action in self.legalActions:
      if bestVal == self.getQValue(state, action):
        if bestAction == [AllActions.STOP]:
          bestAction = [action]
        else:
          bestAction.append(action)
   
    print 'Best Actions', bestAction
    #Return random choice from the bestActions(could use heuristic here but...)
    
    return random.choice(bestAction)
    
    
  #******************************************************************************************
  #getFeatures
  #Big boy here, going to need to predict the next state and then evaluate proper 
  #features that will help the agent distinguish states resulting in rewards
  #******************************************************************************************
  def getFeatures(self, state, action):
    nextState = self.predictNextState(state, action)
    #TODO: DO THIS? Could learn the weights in order to get more accurate prediction? Hopefully NN
    x,y,z = state
    x1,y1,z1 = nextState
    
    features = util.Counter()
    
    features["bias"] = 1.0
    features["distToGoal"] = float(math.fabs(z1 - self.goal[2]))/180
    
    if z1 >= (self.goal[2]-.3) and z1 <= (self.goal[2]+.3):
      features["atGoal"] = 1 
      features["distToGoal"] = 0
      print 'AT GOAL'
    
    return features
  
  #******************************************************************************************
  #update
  #Updates values of the weights at the beginning of turn. If it is the first step, it should
  #return
  #******************************************************************************************
  def update(self, nextState, reward):
    #TODO: Reward in chooseAction/ensure the need to only call chooseAction
  
    #TODO: This maybe needs to be 0?
    if len(self.states) <=1:
      print 'First turn, this should appear once'
      return
    
    
    
      
    currentState = self.states[-1] #TODO: make sure this goes 1 state back!
    action = self.actions[-1] #TODO: Same^^^ Hope to god these line up
    features = self.getFeatures(currentState,action)
    
    print 'Diff', currentState[2] - nextState[2]
    
    
    #For relevant features, adjust weight
    for k in features.sortedKeys():
      correction = (reward + self.discount*self.getValue(nextState) - self.getQValue(currentState, action))
      self.weights[k] += self.alpha*correction*features[k]
      
    return
    
    
    
  #******************************************************************************************
  #predictNextState
  #Bad predictor of the value of the next state given the current state and action
  #******************************************************************************************
  def predictNextState(self, state, action):
    
    x,y,z = state
    zout = z
    if action == AllActions.UP:
      zout = z + 2
    if action == AllActions.DOWN:
      zout = z - 2
    if action == AllActions.FUP:
      zout = z + 4
    if action == AllActions.FDOWN:
      zout = z - 4
    if action == AllActions.SUP:
      zout = z + 1
    if action == AllActions.SDOWN:
      zout = z - 1
    if action == AllActions.STOP:
      print 'Stop'
    return (x,y,zout)
	
  
  
  
class AllActions:
  FDOWN = '-150'
  FUP = '150'
  UP = '60'
  DOWN = '-60'
  SUP = '30'
  SDOWN = '-30'
  STOP = '0'

  
  
  
  
    