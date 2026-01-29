# IAM Privilege Escalation Attempt Playbook

## 1. Alert Overview
- **Severity:** High
- **Category:** Privilege Escalation
- **Data Source:** AWS CloudTrail
- **Trigger Condition:** A denied attempt to attach high-privilege IAM policies

## 2. Why This Alert Matters
Privilege escalation attempts often indicate a compromised identity attempting to gain administrative access. Even failed attempts provide strong evidence of malicious intent or misconfigured automation.

## 3. Initial Triage (First 5 Minutes)
- Identify IAM user or role involved
- Confirm source IP address and region
- Determine whether the action was denied or succeeded
- Check whether the user normally manages IAM

## 4. Investigation Steps
### Review the triggering event
```sql
fields @timestamp, eventName, errorCode, userIdentity.userName, sourceIPAddress, userAgent
| filter eventName="AttachUserPolicy"
| sort @timestamp desc
```
## 5. False Positive Analysis

Possible benign causes:
- Testing environments
- Personel testing permissions
- misconfigured automation

Validate:
- Confirm user role responisbilities
- Reviewing historical behavior
- Check tickets

## 6. Containment Actions
- Restrict IAM permissions temporarily
- Disable keys if external IP
- Force password reset if suspected compromise

## 7. Eradication & Recovery
- Rotate credentials
- Review IAM for least privilege
- Force password reset if suspected compromise

## 8. Post-Incident Improvements
- Correlate with IAM enumeration alerts
- Tune threshold based on environment baseline
