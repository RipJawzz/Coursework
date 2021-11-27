import boto3
import time

client=boto3.client('elasticbeanstalk')

def cloudFront_distribution():
    print('hi')
    response = client.create_distribution(
            DistributionConfig={
                'CallerReference': 'my-distribution-cdn',
                
                'DefaultRootObject': 'index.html',
                'Origins': {
                    'Quantity':1,
                    
                    'Items': [
                        {
                            'Id':'lab3dynamicwebsite',
                            'DomainName': 'lab3dynamicwebsite.s3.us-east-1.amazonaws.com',
                        
                            
                            'S3OriginConfig': {
                                'OriginAccessIdentity': ''
                            },
                           
                        
                        },
                    ]
                },
             'DefaultCacheBehavior': {
                'TargetOriginId': 'lab3dynamicwebsite',
                
               
                'ViewerProtocolPolicy': 'allow-all',
                'AllowedMethods': {
                    'Quantity': 1,
                    'Items': [
                        'GET','HEAD','POST','PUT','PATCH','OPTIONS','DELETE',
                    ],
                    'CachedMethods': {
                        'Quantity': 1,
                        'Items': [
                            'GET','HEAD','POST','PUT','PATCH','OPTIONS','DELETE',
                        ]
                    }
                },
        },
        'Comment':'distribution to host portfolio',
        'Enabled':True,

    }
    )
    print(response)
    


def create_version():
    response = client.create_application_version(
        ApplicationName='LolNoob',
        AutoCreateApplication=True,
        Description='my-app-v4',
        Process=True,
        SourceBundle={
        'S3Bucket': 'awsbucketboi',
        'S3Key': 'deploy_dash_v0.zip',
        },
        VersionLabel='v1',

    )
    print(response)

def create_environment():
    
    response = client.create_environment(
        ApplicationName='LolNoob',
        CNAMEPrefix='LolNoob',
        EnvironmentName='LolNoobenv',
        SolutionStackName='64bit Amazon Linux 2 v3.3.5 running PHP 8.0',
        VersionLabel='v1',
        OptionSettings=[
        {
            'Namespace':'aws:autoscaling:launchconfiguration',
            'OptionName': 'IamInstanceProfile',
            'Value':'EMR_EC2_DefaultRole'
            
            
        },{
            'Namespace':'aws:autoscaling:launchconfiguration',
            'OptionName': 'EC2KeyName',
            'Value':'AWS-Boi'
        },{
            'Namespace':'aws:autoscaling:asg',
            'OptionName':'MaxSize',
            'Value':'2'
        }
    ],
    )
    
    print(response)

if __name__ == "__main__":
    #cloudFront_distribution()
    create_version()
    time.sleep(5)
    create_environment()